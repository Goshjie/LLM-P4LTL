# LLM-P4LTL

这个目录里放的是一个可运行的 hook 原型：

- `upstream/`：复制出来的相关 upstream 代码
- `hooks/`：hook 入口和实际 C++ parser runner
- `program_a/`：模拟的程序 A
- `tests/`：示例测试
- `output/`：输出的 JSON

## 运行前准备

需要本机有：

- `python3`
- `g++`
- `bison`
- `flex`

## 最常用的运行方式

在 `LLM-P4LTL` 目录下执行：

```bash
python3 hooks/p4ltl_hook_pipeline.py \
  --p4 upstream/Artifact/benchmark/Temporal\ Verification/Case\ Study/P4NIS/main.p4 \
  --p4ltl upstream/Artifact/benchmark/Temporal\ Verification/Case\ Study/P4NIS/9.p4ltl \
  --program-a "python3 program_a/save_json_sink.py --output-dir output/program_a"
```

这个命令会做三件事：

1. 自动编译 `hooks/p4ltl_hook_runner.cpp`
2. 用复制出来的 **实际 C++ P4LTL parser** 解析 `.p4ltl`
3. 生成 JSON 并通过 stdin 发给程序 A，程序 A 会把 JSON 保存到 `output/program_a/`

## 全流程包装入口

如果你希望按真正的 `Check.sh -> translator -> validator` 流程来跑，同时在前面导出 hook JSON，就用这个包装脚本：

```bash
bash run_full_flow_with_hook.sh \
  "samples/P4NIS/main.p4" \
  "samples/P4NIS/9.p4ltl"
```

这个脚本现在会：

1. 先运行 **hook0**，直接从原始 `.p4ltl` 导出一份 JSON
2. 再调用真实的 `p4c-translator`
3. translator 生成 `.bpl` 后，运行 **hook1**，从 Boogie 中抽取 pre-validator constraints JSON
4. 再调用真实的 validator `Check.sh`
5. validator 结束后再运行 **hook2**，把 oracle/result JSON 发给 Program A 并保存

## P4NIS 示例

### 输入文件

- P4 程序：`upstream/Artifact/benchmark/Temporal Verification/Case Study/P4NIS/main.p4`
- P4LTL 规格：`upstream/Artifact/benchmark/Temporal Verification/Case Study/P4NIS/9.p4ltl`

### 运行命令

```bash
python3 hooks/p4ltl_hook_pipeline.py \
  --p4 "upstream/Artifact/benchmark/Temporal Verification/Case Study/P4NIS/main.p4" \
  --p4ltl "upstream/Artifact/benchmark/Temporal Verification/Case Study/P4NIS/9.p4ltl" \
  --program-a "python3 program_a/save_json_sink.py --output-dir output/program_a" \
  --dump-json output/last_hook_event.json
```

### 运行结果

成功后你会看到类似输出：

```text
Built /home/gosh/P4LTL/LLM-P4LTL/build/p4ltl_hook_runner
/home/gosh/P4LTL/LLM-P4LTL/output/program_a/20260317T144543Z_event-....json
```

这说明：

- parser runner 编译成功
- Program A 成功收到了 JSON
- JSON 已经保存到 `output/program_a/`

### 输出文件

主要看两个地方：

- Program A 保存的文件：`output/program_a/*.json`
- 额外导出的最后一次 hook0 结果：`output/last_hook_event.json`
- 额外导出的最后一次 hook1 结果：`output/last_hook1_event.json`
- 额外导出的最后一次 oracle 结果：`output/last_oracle_event.json`

## 一键测试

如果你只想直接验证整条链路能跑通，可以执行：

```bash
python3 tests/test_p4nis_demo.py
```

它会自动：

- 跑 P4NIS 示例
- 检查 Program A 是否真的保存了 JSON

## 当前原型做了什么

当前版本会：

- 运行实际复制过来的 C++ P4LTL parser
- 解析 `.p4ltl` 里的：
  - `#LTLVariables`
  - `#LTLProperty`
  - `#LTLFairness`
  - `#CPI*`
  - `#register_write`
- 导出 JSON
- 按保守规则拆成：
  - `packet_constraints`
  - `environment_constraints`
- 在真实 validator 完成后，再从日志中提取最终 `oracle`

## 当前实现状态

当前已经可以这样跑：

- 先运行复制出来的真实 C++ P4LTL parser
- 把 hook JSON 发给 Program A 并保存
- 再继续跑真实的 `Check.sh -> translator -> validator`
- validator 结束后再把 oracle JSON 发给 Program A 并保存

也就是说，**全流程已经能走通，并且两个 hook 都已经接进真实的 `Check.sh` 路径里**；只是 hook2 目前是从 validator 的真实输出日志提取结果，而不是直接改 Java 内部结果对象。
