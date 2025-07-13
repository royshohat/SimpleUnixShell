# Simple UNIX Shell

## Overview

this project is a minimal shell implemented in C. It demonstrates fundamental Unix programming concepts like process creation with `fork`, command execution via `execvp`, inter-process communication using `pipe`, and file descriptor redirection using `dup2`.

It supports execution of single or multiple piped commands and handles built-in commands such as `cd`, `pwd`, and `exit` internally. Input is continuously accepted until the user exits or signals EOF.

## Implementation

The shell parses input using `parseForPipe` to separate piped segments, and `parseToArgs` to split each segment into arguments. It creates child processes for each command, sets up pipes between them when needed, and manages file descriptors carefully to avoid leaks or hanging processes.

## Building

To compile and run:

```
make sh
```
