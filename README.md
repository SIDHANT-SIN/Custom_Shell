# Custom Shell in C

This project is a simple Unix-like shell implemented in C.  
It supports basic built-in commands and can execute external programs.

## Features

- Built-in commands:
  - `ls` (internal implementation to list files, skips hidden files)
  - `pwd` (print current working directory)
  - `cd` (change directory)
  - `echo` (print arguments to the console)
  - `exit` (exit the shell)

- External command execution using `fork()` and `execvp()`.

- Input parsing using `getline()` and `strtok()`.

## How to compile and run

```bash
gcc -o my_shell custom_shell.c
./my_shell

