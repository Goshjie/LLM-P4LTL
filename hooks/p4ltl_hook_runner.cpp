#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>

#include "frontends/parsers/p4ltl/p4ltlast.hpp"
#include "frontends/parsers/p4ltl/p4ltlparser.hpp"
#include "frontends/parsers/p4ltl/p4ltllexer.hpp"

namespace {

struct MarkerLine {
    std::string marker;
    std::string logicalName;
    int lineNo;
    std::string content;
};

const std::map<std::string, std::string> kMarkers = {
    {"//#LTLVariables:", "ltl_variables"},
    {"//#LTLProperty:", "ltl_property"},
    {"//#LTLFairness:", "ltl_fairness"},
    {"//#CPI:", "cpi"},
    {"//#CPI_MODEL:", "cpi_model"},
    {"//#CPI_SPEC:", "cpi_spec"},
    {"//#CPI_SIMP:", "cpi_simp"},
    {"//#register_write", "register_write"},
};

std::string trim(const std::string& input) {
    const auto first = input.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = input.find_last_not_of(" \t\r\n");
    return input.substr(first, last - first + 1);
}

std::string jsonEscape(const std::string& input) {
    std::ostringstream output;
    for (char ch : input) {
        switch (ch) {
            case '\\': output << "\\\\"; break;
            case '"': output << "\\\""; break;
            case '\n': output << "\\n"; break;
            case '\r': output << "\\r"; break;
            case '\t': output << "\\t"; break;
            default: output << ch; break;
        }
    }
    return output.str();
}

std::vector<MarkerLine> extractMarkers(const std::string& p4ltlPath) {
    std::ifstream input(p4ltlPath);
    if (!input) {
        throw std::runtime_error("Failed to open P4LTL file: " + p4ltlPath);
    }
    std::vector<MarkerLine> result;
    std::string line;
    int lineNo = 0;
    while (std::getline(input, line)) {
        ++lineNo;
        for (const auto& [marker, logical] : kMarkers) {
            if (line.rfind(marker, 0) == 0) {
                result.push_back({marker, logical, lineNo, trim(line.substr(marker.size()))});
                break;
            }
        }
    }
    return result;
}

P4LTL::AstNode* parseFormula(const std::string& formula) {
    std::istringstream formulaStream(formula);
    P4LTL::Scanner scanner{formulaStream, std::cerr};
    P4LTL::AstNode* root = nullptr;
    P4LTL::P4LTLParser parser{scanner, root};
    const int result = parser.parse();
    if (result != 0 || root == nullptr) {
        throw std::runtime_error("Failed to parse P4LTL formula: " + formula);
    }
    return root;
}

std::vector<std::string> extractAtomicProps(const std::string& formula) {
    static const std::regex pattern(R"(AP\((.*?)\))");
    std::vector<std::string> result;
    auto begin = std::sregex_iterator(formula.begin(), formula.end(), pattern);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        result.push_back(trim((*it)[1].str()));
    }
    return result;
}

std::vector<std::string> extractFields(const std::string& formula) {
    static const std::regex pattern(R"((?:old\()?(?:hdr|meta|standard_metadata)\.[A-Za-z0-9_\.]+(?:\))?)");
    std::set<std::string> fields;
    auto begin = std::sregex_iterator(formula.begin(), formula.end(), pattern);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        fields.insert((*it).str());
    }
    return std::vector<std::string>(fields.begin(), fields.end());
}

bool isPacketConstraint(const std::string& expr) {
    return expr.find("fwd(") != std::string::npos ||
           expr.find("drop") != std::string::npos ||
           expr.find("valid(") != std::string::npos ||
           std::regex_search(expr, std::regex(R"((?:hdr|meta|standard_metadata)\.)"));
}

void appendJsonStringArray(std::ostringstream& output, const std::vector<std::string>& values) {
    output << "[";
    for (std::size_t index = 0; index < values.size(); ++index) {
        if (index != 0) {
            output << ",";
        }
        output << "\"" << jsonEscape(values[index]) << "\"";
    }
    output << "]";
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: p4ltl_hook_runner <p4-file> <p4ltl-file>\n";
        return 1;
    }

    const std::string p4Path = argv[1];
    const std::string p4ltlPath = argv[2];

    try {
        const auto markers = extractMarkers(p4ltlPath);

        struct ParsedFormula {
            MarkerLine marker;
            std::string normalized;
        };
        std::vector<ParsedFormula> parsedFormulas;

        std::vector<std::string> packetConstraintEntries;
        std::vector<std::string> environmentConstraintEntries;
        std::map<std::string, std::vector<std::string>> rawSections;

        for (const auto& marker : markers) {
            rawSections[marker.logicalName].push_back(marker.content);

            if (marker.logicalName == "ltl_property" || marker.logicalName == "ltl_fairness" ||
                marker.logicalName == "cpi" || marker.logicalName == "cpi_model" ||
                marker.logicalName == "cpi_spec") {
                P4LTL::AstNode* root = parseFormula(marker.content);
                const std::string normalized = root->toString();
                parsedFormulas.push_back({marker, normalized});

                if (marker.logicalName == "ltl_fairness") {
                    std::ostringstream entry;
                    entry << "{\"source\":\"" << marker.logicalName << "\",\"line\":" << marker.lineNo
                          << ",\"expression\":\"" << jsonEscape(normalized) << "\",\"fields\":";
                    appendJsonStringArray(entry, extractFields(normalized));
                    entry << "}";
                    environmentConstraintEntries.push_back(entry.str());
                }

                for (const auto& ap : extractAtomicProps(normalized)) {
                    std::ostringstream entry;
                    entry << "{\"source\":\"" << marker.logicalName << "\",\"line\":" << marker.lineNo
                          << ",\"expression\":\"" << jsonEscape(ap) << "\",\"fields\":";
                    appendJsonStringArray(entry, extractFields(ap));
                    entry << "}";
                    if (isPacketConstraint(ap)) {
                        packetConstraintEntries.push_back(entry.str());
                    } else {
                        environmentConstraintEntries.push_back(entry.str());
                    }
                }
            } else if (marker.logicalName == "cpi_simp") {
                std::ostringstream entry;
                entry << "{\"source\":\"" << marker.logicalName << "\",\"line\":" << marker.lineNo
                      << ",\"expression\":\"" << jsonEscape(marker.content) << "\",\"fields\":";
                appendJsonStringArray(entry, extractFields(marker.content));
                entry << "}";
                environmentConstraintEntries.push_back(entry.str());
            } else if (marker.logicalName == "register_write") {
                std::istringstream iss(marker.content);
                std::string reg;
                std::string index;
                std::string value;
                iss >> reg >> index;
                std::getline(iss, value);
                value = trim(value);
                std::ostringstream entry;
                entry << "{\"source\":\"" << marker.logicalName << "\",\"line\":" << marker.lineNo
                      << ",\"register\":\"" << jsonEscape(reg) << "\",\"index\":\"" << jsonEscape(index)
                      << "\",\"value\":\"" << jsonEscape(value) << "\"}";
                environmentConstraintEntries.push_back(entry.str());
            } else if (marker.logicalName == "ltl_variables") {
                std::vector<std::string> vars;
                std::istringstream iss(marker.content);
                std::string token;
                while (std::getline(iss, token, ',')) {
                    token = trim(token);
                    if (!token.empty()) {
                        vars.push_back(token);
                    }
                }
                std::ostringstream entry;
                entry << "{\"source\":\"" << marker.logicalName << "\",\"line\":" << marker.lineNo
                      << ",\"variables\":";
                appendJsonStringArray(entry, vars);
                entry << "}";
                environmentConstraintEntries.push_back(entry.str());
            }
        }

        std::ostringstream output;
        const auto now = std::chrono::system_clock::now().time_since_epoch().count();
        output << "{";
        output << "\"hook_version\":2,";
        output << "\"event_id\":\"event-" << now << "\",";
        output << "\"stage\":\"pre_solver_constraints_actual_parser\",";
        output << "\"source\":{";
        output << "\"p4_path\":\"" << jsonEscape(p4Path) << "\",";
        output << "\"p4ltl_path\":\"" << jsonEscape(p4ltlPath) << "\"},";

        output << "\"parsed_formulas\":[";
        for (std::size_t index = 0; index < parsedFormulas.size(); ++index) {
            if (index != 0) {
                output << ",";
            }
            output << "{"
                   << "\"source\":\"" << parsedFormulas[index].marker.logicalName << "\","
                   << "\"line\":" << parsedFormulas[index].marker.lineNo << ","
                   << "\"original\":\"" << jsonEscape(parsedFormulas[index].marker.content) << "\","
                   << "\"normalized\":\"" << jsonEscape(parsedFormulas[index].normalized) << "\""
                   << "}";
        }
        output << "],";

        output << "\"raw_sections\":{";
        bool firstSection = true;
        for (const auto& [section, values] : rawSections) {
            if (!firstSection) {
                output << ",";
            }
            firstSection = false;
            output << "\"" << jsonEscape(section) << "\":";
            appendJsonStringArray(output, values);
        }
        output << "},";

        output << "\"packet_constraints\":[";
        for (std::size_t index = 0; index < packetConstraintEntries.size(); ++index) {
            if (index != 0) {
                output << ",";
            }
            output << packetConstraintEntries[index];
        }
        output << "],";

        output << "\"environment_constraints\":[";
        for (std::size_t index = 0; index < environmentConstraintEntries.size(); ++index) {
            if (index != 0) {
                output << ",";
            }
            output << environmentConstraintEntries[index];
        }
        output << "],";

        output << "\"notes\":["
               << "\"This JSON is produced by the actual copied C++ P4LTL parser (flex+bison generated at build time).\","
               << "\"It is still a hook prototype and not yet inserted into the full upstream translator or validator main loop.\""
               << "]}";

        std::cout << output.str() << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}
