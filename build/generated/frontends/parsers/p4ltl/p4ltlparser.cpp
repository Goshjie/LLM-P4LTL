// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "p4ltlparser.hpp"


// Unqualified %code blocks.
#line 28 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"

    #include "frontends/parsers/p4ltl/p4ltllexer.hpp"    
    #undef yylex
    #define yylex(x) scanner.lex(x)

#line 51 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
namespace P4LTL {
#line 124 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  P4LTLParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  P4LTLParser::P4LTLParser (Scanner& scanner_yyarg, AstNode*& root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  P4LTLParser::~P4LTLParser ()
  {}

  P4LTLParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  P4LTLParser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
  {
    switch (this->type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.move< AstNode* > (std::move (that.value));
        break;

      case 35: // NAME
        value.move< char* > (std::move (that.value));
        break;

      case 36: // INT
        value.move< unsigned long long int > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  P4LTLParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.copy< AstNode* > (YY_MOVE (that.value));
        break;

      case 35: // NAME
        value.copy< char* > (YY_MOVE (that.value));
        break;

      case 36: // INT
        value.copy< unsigned long long int > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  P4LTLParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  P4LTLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.move< AstNode* > (YY_MOVE (s.value));
        break;

      case 35: // NAME
        value.move< char* > (YY_MOVE (s.value));
        break;

      case 36: // INT
        value.move< unsigned long long int > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_type.
  P4LTLParser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  P4LTLParser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  P4LTLParser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  P4LTLParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  P4LTLParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  P4LTLParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  P4LTLParser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  P4LTLParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  P4LTLParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  P4LTLParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  P4LTLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  P4LTLParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  P4LTLParser::symbol_number_type
  P4LTLParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  P4LTLParser::stack_symbol_type::stack_symbol_type ()
  {}

  P4LTLParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.YY_MOVE_OR_COPY< AstNode* > (YY_MOVE (that.value));
        break;

      case 35: // NAME
        value.YY_MOVE_OR_COPY< char* > (YY_MOVE (that.value));
        break;

      case 36: // INT
        value.YY_MOVE_OR_COPY< unsigned long long int > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  P4LTLParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.move< AstNode* > (YY_MOVE (that.value));
        break;

      case 35: // NAME
        value.move< char* > (YY_MOVE (that.value));
        break;

      case 36: // INT
        value.move< unsigned long long int > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  P4LTLParser::stack_symbol_type&
  P4LTLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.copy< AstNode* > (that.value);
        break;

      case 35: // NAME
        value.copy< char* > (that.value);
        break;

      case 36: // INT
        value.copy< unsigned long long int > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  P4LTLParser::stack_symbol_type&
  P4LTLParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        value.move< AstNode* > (that.value);
        break;

      case 35: // NAME
        value.move< char* > (that.value);
        break;

      case 36: // INT
        value.move< unsigned long long int > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  P4LTLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  P4LTLParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  P4LTLParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  P4LTLParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  P4LTLParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  P4LTLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  P4LTLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  P4LTLParser::debug_level_type
  P4LTLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  P4LTLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  P4LTLParser::state_type
  P4LTLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  P4LTLParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  P4LTLParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  P4LTLParser::operator() ()
  {
    return parse ();
  }

  int
  P4LTLParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 41: // p4ltl
      case 42: // texpr
      case 43: // predicate
      case 44: // term
      case 45: // identifier
        yylhs.value.emplace< AstNode* > ();
        break;

      case 35: // NAME
        yylhs.value.emplace< char* > ();
        break;

      case 36: // INT
        yylhs.value.emplace< unsigned long long int > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 67 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
    {yylhs.value.as < AstNode* > () = yystack_[0].value.as < AstNode* > (); root = yylhs.value.as < AstNode* > ();
    }
#line 758 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 3:
#line 72 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::And, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ());}
#line 764 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 4:
#line 75 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::Or, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 770 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 5:
#line 78 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::Implies, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 776 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 6:
#line 81 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::Until, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 782 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 7:
#line 84 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        { // a W b == Ga || a U b
        AstNode* globala = new UnaryTemporalOperator(UnaryTemporalOperator::UnaryTemporalOperatorType::Global, yystack_[2].value.as < AstNode* > ());
        AstNode* aUb = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::Until, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ());
        yylhs.value.as < AstNode* > () = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::Or, 
                globala, aUb);
    }
#line 793 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 8:
#line 92 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTemporalOperator(BinaryTemporalOperator::BinaryTemporalOperatorType::Release, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 799 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 9:
#line 95 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new UnaryTemporalOperator(UnaryTemporalOperator::UnaryTemporalOperatorType::Global, yystack_[1].value.as < AstNode* > ());}
#line 805 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 10:
#line 98 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new UnaryTemporalOperator(UnaryTemporalOperator::UnaryTemporalOperatorType::Final, yystack_[1].value.as < AstNode* > ()); }
#line 811 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 11:
#line 101 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new UnaryTemporalOperator(UnaryTemporalOperator::UnaryTemporalOperatorType::Next, yystack_[1].value.as < AstNode* > ()); }
#line 817 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 12:
#line 104 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new UnaryTemporalOperator(UnaryTemporalOperator::UnaryTemporalOperatorType::Not, yystack_[0].value.as < AstNode* > ()); }
#line 823 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 13:
#line 107 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = yystack_[1].value.as < AstNode* > (); }
#line 829 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 14:
#line 110 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new P4LTLAtomicProposition(yystack_[1].value.as < AstNode* > ()); }
#line 835 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 15:
#line 115 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Drop(); }
#line 841 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 16:
#line 117 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Forward(yystack_[1].value.as < AstNode* > ()); }
#line 847 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 17:
#line 119 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Apply(yystack_[1].value.as < char* > ()); }
#line 853 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 18:
#line 121 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Apply(yystack_[3].value.as < char* > (), yystack_[1].value.as < char* > ()); }
#line 859 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 19:
#line 123 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Valid(yystack_[1].value.as < char* > ()); }
#line 865 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 20:
#line 125 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new ExtendedComparativeOperator(ExtendedComparativeOperator::ExtendedComparativeOperatorType::eq, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 871 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 21:
#line 127 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new ExtendedComparativeOperator(ExtendedComparativeOperator::ExtendedComparativeOperatorType::gt, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 877 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 22:
#line 129 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new ExtendedComparativeOperator(ExtendedComparativeOperator::ExtendedComparativeOperatorType::geq, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 883 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 23:
#line 131 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new ExtendedComparativeOperator(ExtendedComparativeOperator::ExtendedComparativeOperatorType::neq, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 889 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 24:
#line 133 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new ExtendedComparativeOperator(ExtendedComparativeOperator::ExtendedComparativeOperatorType::lt, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 895 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 25:
#line 135 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new ExtendedComparativeOperator(ExtendedComparativeOperator::ExtendedComparativeOperatorType::leq, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 901 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 26:
#line 138 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryPredicateOperator(BinaryPredicateOperator::BinaryPredicateOperatorType::And, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 907 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 27:
#line 140 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryPredicateOperator(BinaryPredicateOperator::BinaryPredicateOperatorType::Or, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 913 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 28:
#line 142 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryPredicateOperator(BinaryPredicateOperator::BinaryPredicateOperatorType::Implies, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 919 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 29:
#line 144 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = yystack_[1].value.as < AstNode* > (); }
#line 925 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 30:
#line 146 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new UnaryPredicateOperator(UnaryPredicateOperator::UnaryPredicateOperatorType::Not, yystack_[0].value.as < AstNode* > ()); }
#line 931 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 31:
#line 155 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {// currently we don't support multiaccessor
        yylhs.value.as < AstNode* > () = new ArrayAccessExprssion(yystack_[3].value.as < AstNode* > (),yystack_[1].value.as < AstNode* > ()); }
#line 938 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 32:
#line 160 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new OldExpression(yystack_[1].value.as < AstNode* > ()); }
#line 944 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 33:
#line 162 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Key(yystack_[3].value.as < char* > (), yystack_[1].value.as < char* > ()); }
#line 950 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 34:
#line 164 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTermOperator(BinaryTermOperator::BinaryTermOperatorType::Plus, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 956 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 35:
#line 166 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTermOperator(BinaryTermOperator::BinaryTermOperatorType::Minus, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 962 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 36:
#line 168 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BinaryTermOperator(BinaryTermOperator::BinaryTermOperatorType::Multiply, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 968 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 37:
#line 170 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
    {yylhs.value.as < AstNode* > () = new BinaryTermOperator(BinaryTermOperator::BinaryTermOperatorType::Divide, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 974 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 38:
#line 172 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
    {yylhs.value.as < AstNode* > () = new BinaryTermOperator(BinaryTermOperator::BinaryTermOperatorType::Mod, yystack_[2].value.as < AstNode* > (), yystack_[0].value.as < AstNode* > ()); }
#line 980 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 39:
#line 174 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = yystack_[1].value.as < AstNode* > (); }
#line 986 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 40:
#line 176 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = yystack_[0].value.as < AstNode* > (); }
#line 992 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 41:
#line 178 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new IntLiteral(yystack_[0].value.as < unsigned long long int > ()); }
#line 998 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 42:
#line 180 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BooleanLiteral(true); }
#line 1004 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 43:
#line 182 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new BooleanLiteral(false); }
#line 1010 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;

  case 44:
#line 187 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
        {yylhs.value.as < AstNode* > () = new Name(yystack_[0].value.as < char* > ()); }
#line 1016 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"
    break;


#line 1020 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  P4LTLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  P4LTLParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char P4LTLParser::yypact_ninf_ = -23;

  const signed char P4LTLParser::yytable_ninf_ = -1;

  const short
  P4LTLParser::yypact_[] =
  {
       5,     1,     5,     4,     6,    12,     5,    29,   175,    90,
      98,     5,     5,     5,   -23,   -23,     5,     5,     5,     5,
       5,     5,    90,    25,   -23,    27,    48,    90,    49,    51,
     -23,   -23,   -23,   -23,   114,   124,    -6,   -23,   149,   161,
     168,   -23,   -23,   -23,   113,   -12,   175,   152,    46,    22,
      31,    24,   -23,    31,    33,   -23,    90,    90,    90,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,   -23,   -23,   -23,   -23,   -23,    10,    31,    -4,    54,
      52,    78,   -23,    79,    67,   -13,   -13,    68,    68,   -13,
     -13,   -13,   -13,   -23,   -23,   -23,    71,    76,   -23,    55,
     -23,   -23,   -23,    81,   -23,    97,   126,   -23,   -23
  };

  const signed char
  P4LTLParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       0,     0,     0,     0,    12,     1,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,     0,     0,     0,
      42,    43,    44,    41,     0,     0,    40,    13,     0,     0,
       0,     6,     7,     8,     3,     4,     5,     0,     0,     0,
       0,     0,    30,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    29,    39,     0,     0,     0,     0,
       0,     0,    26,    27,    28,    20,    23,    34,    35,    21,
      22,    24,    25,    36,    37,    38,     0,     0,    17,     0,
      16,    19,    32,     0,    31,     0,     0,    18,    33
  };

  const signed char
  P4LTLParser::yypgoto_[] =
  {
     -23,   -23,   125,    -7,   -22,   -23
  };

  const signed char
  P4LTLParser::yydefgoto_[] =
  {
      -1,     7,     8,    34,    35,    36
  };

  const signed char
  P4LTLParser::yytable_[] =
  {
      48,    70,   100,    16,    17,    18,     9,    19,     1,    11,
       2,    12,    61,    62,    97,    47,    98,    13,     3,     4,
      52,    61,    62,     5,    67,    68,    69,     6,    78,    15,
      49,    80,    50,    67,    68,    69,    77,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    82,
      83,    84,    75,    51,    53,    99,    54,    76,   102,    79,
     101,    75,    28,    29,    30,    31,    32,    33,    81,    59,
      60,    61,    62,    63,    64,    65,    66,    61,    62,   104,
      61,    62,   103,    67,    68,    69,    56,    57,    58,    67,
      68,    69,    67,    68,    69,    22,    61,    62,    56,    23,
      24,    25,    26,   107,    37,    67,    68,    69,    67,    68,
      69,   105,    27,    16,    17,    18,   106,    19,    20,    21,
      55,    28,    29,    30,    31,    32,    33,    10,    16,    17,
      18,    14,   108,    56,    57,    58,    38,    39,    40,     0,
       0,    41,    42,    43,    44,    45,    46,    59,    60,    61,
      62,    63,    64,    65,    66,    71,     0,     0,    74,     0,
       0,    67,    68,    69,    16,    17,    18,    72,    19,    20,
      21,    56,    57,    58,    73,     0,    16,    17,    18,     0,
      19,    20,    21,    16,    17,    18,     0,    19,    20,    21,
      16,    17,    18,     0,    19,    20,    21
  };

  const signed char
  P4LTLParser::yycheck_[] =
  {
      22,     7,     6,    15,    16,    17,     5,    19,     3,     5,
       5,     5,    25,    26,     4,    22,     6,     5,    13,    14,
      27,    25,    26,    18,    37,    38,    39,    22,    50,     0,
       5,    53,     5,    37,    38,    39,     5,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    56,
      57,    58,     6,     5,     5,    77,     5,    35,     6,    35,
       6,     6,    31,    32,    33,    34,    35,    36,    35,    23,
      24,    25,    26,    27,    28,    29,    30,    25,    26,     8,
      25,    26,     4,    37,    38,    39,    19,    20,    21,    37,
      38,    39,    37,    38,    39,     5,    25,    26,    19,     9,
      10,    11,    12,     6,     6,    37,    38,    39,    37,    38,
      39,    35,    22,    15,    16,    17,    35,    19,    20,    21,
       6,    31,    32,    33,    34,    35,    36,     2,    15,    16,
      17,     6,     6,    19,    20,    21,    11,    12,    13,    -1,
      -1,    16,    17,    18,    19,    20,    21,    23,    24,    25,
      26,    27,    28,    29,    30,     6,    -1,    -1,     6,    -1,
      -1,    37,    38,    39,    15,    16,    17,     6,    19,    20,
      21,    19,    20,    21,     6,    -1,    15,    16,    17,    -1,
      19,    20,    21,    15,    16,    17,    -1,    19,    20,    21,
      15,    16,    17,    -1,    19,    20,    21
  };

  const signed char
  P4LTLParser::yystos_[] =
  {
       0,     3,     5,    13,    14,    18,    22,    41,    42,     5,
      42,     5,     5,     5,    42,     0,    15,    16,    17,    19,
      20,    21,     5,     9,    10,    11,    12,    22,    31,    32,
      33,    34,    35,    36,    43,    44,    45,     6,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    43,    44,     5,
       5,     5,    43,     5,     5,     6,    19,    20,    21,    23,
      24,    25,    26,    27,    28,    29,    30,    37,    38,    39,
       7,     6,     6,     6,     6,     6,    35,     5,    44,    35,
      44,    35,    43,    43,    43,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,     4,     6,    44,
       6,     6,     6,     4,     8,    35,    35,     6,     6
  };

  const signed char
  P4LTLParser::yyr1_[] =
  {
       0,    40,    41,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    45
  };

  const signed char
  P4LTLParser::yyr2_[] =
  {
       0,     2,     1,     3,     3,     3,     3,     3,     3,     4,
       4,     4,     2,     3,     4,     1,     4,     4,     6,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     4,     4,     6,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const P4LTLParser::yytname_[] =
  {
  "$end", "error", "$undefined", "AP", "COMMA", "LPAR", "RPAR",
  "LBRACKET", "RBRACKET", "APPLY", "DROP", "FWD", "VALID", "ALWAYS",
  "EVENTUALLY", "UNTIL", "WEAKUNTIL", "RELEASE", "NEXT", "AND", "OR",
  "IMPLIES", "NEG", "EQ", "NEQ", "PLUS", "MINUS", "GT", "GEQ", "LT", "LEQ",
  "OLD", "KEY", "TRUE", "FALSE", "NAME", "INT", "MULTIPLY", "DIVIDE",
  "MOD", "$accept", "p4ltl", "texpr", "predicate", "term", "identifier", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  P4LTLParser::yyrline_[] =
  {
       0,    66,    66,    71,    74,    77,    80,    83,    91,    94,
      97,   100,   103,   106,   109,   114,   116,   118,   120,   122,
     124,   126,   128,   130,   132,   134,   137,   139,   141,   143,
     145,   154,   159,   161,   163,   165,   167,   169,   171,   173,
     175,   177,   179,   181,   186
  };

  // Print the state stack on the debug stream.
  void
  P4LTLParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  P4LTLParser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  P4LTLParser::token_number_type
  P4LTLParser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
    };
    const int user_token_number_max_ = 294;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

#line 5 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"
} // P4LTL
#line 1528 "/home/gosh/P4LTL/LLM-P4LTL/build/generated/frontends/parsers/p4ltl/p4ltlparser.cpp"

#line 189 "/home/gosh/P4LTL/LLM-P4LTL/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlparser.ypp"

/* void yyerror (const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
} */

void P4LTL::P4LTLParser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}

/* int main()
{
    yyparse();
    // std::cout << "Parse result: " <<  yyparse() << std::endl;
    if(root != nullptr)
        std::cout << "P4LTL: " + root->toString() << std::endl;
    else
        std::cout << "Root is empty. But Why?" << std::endl;
} */
