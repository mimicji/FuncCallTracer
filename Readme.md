# FuncCallTracer

FuncCallTracer is a simple yet powerful function call tracer that records function execution details, leveraging Intel CPU timestamps for precise tracking.

## Features

- Function Call Recording: Captures details about function calls and returns.
- High Precision: Utilizes Intel CPU timestamps for accurate timing.
- Trace Readability: Outputs detailed traces with call stack depth, caller/callee information, and more.

## Dependencies

- Unix-based operating system
- DynamoRIO (version >= 9.0.0)
- libunwind-dev

## Usage

### Build

```bash
$ ./build.sh
```

### Execute

To trace an application:

```bash
$ ./FuncCallTracer.sh \<application\>
```

### Example

```bash
$ ./FuncCallTracer.sh ls
[FuncCallTracer] Start tracing.
[FuncCallTracer] Trace file .../FuncCallTracer/build/calltrace.ls.22457.0000.log created
```

## Trace File Location

During execution, `FuncCallTracer` will notify you where the trace file is saved:

```bash
[FuncCallTracer] Trace file .../FuncCallTracer/build/calltrace.<application>.<pid>.<tid>.log created
```

## Trace File Format

The Call Tracer outputs a detailed trace of function calls and returns, capturing the following information for each operation:

- **Call Stack Depth**

- **Operation Type** (`CALL`, `INDIRECT CALL`, or `RETURN`)

- **Caller and Callee Information**: Memory address, function name, source file, and line number

- **Stack Pointer Value**

- **Timestamp** (high-resolution)

- **CPU Core ID**

### Output Format

```bash
[<Call Stack Depth>] <Operation> @ <address_of_caller> <caller_name> <file:lineNUM>
  to <address_of_callee> <callee_name> <file:lineNUM>
  RSP=<stack_pointer_value>
  Timestamp=<timestamp>, CPU_ID=<cpu_id>
```

## Example Trace Output

```
[0] CALL @  0x00007fd4955fa293 ld-linux-x86-64.so.2!_start+0x3 ??:0
  to  0x00007fd4955fb030 ld-linux-x86-64.so.2!_dl_start+0x0 ./elf/rtld.c:527+0x0
  RSP=0x00007ffce4e340d0
  Timestamp=100197918040376238, CPU_ID=1
[1] CALL @  0x00007fd4955fb517 ld-linux-x86-64.so.2!_dl_start+0x4e7 ./elf/rtld.c:588+0x0
  to  0x00007fd4955f82e0 ld-linux-x86-64.so.2!__rtld_malloc_init_stubs+0x0 ./elf/dl-minimal.c:42+0x0
  RSP=0x00007ffce4e34010
  Timestamp=100197918048105546, CPU_ID=1
[2] RETURN @  0x00007fd4955f831c ld-linux-x86-64.so.2!__rtld_malloc_init_stubs+0x3c ./elf/dl-minimal.c:47+0x0
  to  0x00007fd4955fb51c ld-linux-x86-64.so.2!_dl_start+0x4ec ./elf/rtld.c:592+0x0
  RSP=0x00007ffce4e34008
  Timestamp=100197918049130838, CPU_ID=1
[1] CALL @  0x00007fd4955fb544 ld-linux-x86-64.so.2!_dl_start+0x514 ./elf/rtld.c:488+0x0
  to  0x00007fd4955ed530 ld-linux-x86-64.so.2!_dl_setup_hash+0x0 ./elf/dl-setup_hash.c:25+0x0
  RSP=0x00007ffce4e34010
  Timestamp=100197918049954290, CPU_ID=1
...
```