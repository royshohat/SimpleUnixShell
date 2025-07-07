# 🐚 Simple Unix Shell in C

This project is a lightweight, minimal Unix shell implemented in C. It mimics basic behavior of popular shells like `bash` or `sh`, allowing users to enter and execute commands interactively.

## 🚀 Features

- Command parsing and execution
- Support for built-in commands (e.g., `cd`, `exit`)
- Executes external programs via `fork()` and `execvp()`
- Handles whitespace and argument splitting
- Basic error handling

## 🛠️ Compilation

Use `gcc` to compile:

```bash
gcc -o mysh mysh.c

