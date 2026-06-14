```
                         __  
  _________  ____  _____/ /_ 
 / ___/ __ \/ __ \/ ___/ __ \
/ /__/ /_/ / / / / /__/ / / /
\___/\____/_/ /_/\___/_/ /_/                  

```
# Conch
> Conch is a lightweight Unix shell written in C from scratch.

![Version](https://img.shields.io/badge/version-0.5.0-blue)
![Language](https://img.shields.io/badge/language-C-informational)
![License](https://img.shields.io/badge/license-MIT-green)

## Summary

Conch is a functional Unix shell built entirely in C, implementing the core read-eval-print loop that powers every shell. Conch interfaces directly with the OS through POSIX system calls, managing process creation, execution, and memory manually.

This project was built to develop an understanding of how shells work at the systems level, examining how process forking, executable loading, and the distinction between builtin and external commands is handled.

## Features

- Interactive prompt with a read-eval-print loop (REPL)
- Execution of external system commands through `PATH` resolution
- Builtin commands: `cd`, `exit`, `about`
- Output and input redirection (`>`, `<`)
- Graceful handling of empty input and EOF
- Modular architecture split across focused source files

## Process

When a command is entered, Conch follows this pipeline:

```
Input → Tokenizer (parser.c) → Builtin check (builtins.c) → Execute (shell.c)
                                        ↓                          ↓
                                  Run in-process              fork() + execvp()
```

External commands are executed by forking a child process with `fork()` and replacing it with the target program using `execvp()`. The parent shell blocks with `waitpid()` until the child process exits. Builtin commands like `cd` run directly in the shell process.

## Project Structure

```
conch/
├── main.c          # Entry point and REPL loop
├── parser.c/h      # Tokenizes raw input into an argument array
├── shell.c/h       # Execution logic; routes to builtins or forks a child, checks for redirection
├── builtins.c/h    # Builtin command implementations
└── CMakeLists.txt
```

## Build & Run

**Requirements:** CMake 3.20+, a C11-compatible compiler (GCC or Clang)

```bash
# Clone the repo
git clone https://github.com/carson-js/conch.git
cd conch
 
# Build
cmake -B cmake-build-debug
cmake --build cmake-build-debug
 
# Run
./cmake-build-debug/conch
```

## Planned Features

- Pipes (`|`)
- Command history (up arrow)
- Environment variable expansion (`$HOME`, `$PATH`)
- Background job execution (`&`)

## Author

Built by Carson Smith — [github.com/carson-js](https://github.com/carson-js) · [carsonjs.me](https://carsonjs.me)

## License

MIT License — see [LICENSE](LICENSE) for details.