# Shell Interpreter

## Description

This project is about creating a simple shell interpreter. The shell is a command that reads lines from either a file or the terminal, interprets them, and generally executes other commands. The shell implements a limited set of features. The shell is not a replacement for the sh shell, but rather a simple version of it.

## Usage

The shell works like this in interactive mode:

```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

And in non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Features

The shell interpreter provides the following features:

- Display a prompt and wait for user input.
- Execute commands entered by the user.
- Handle errors gracefully.
- Detect the "end of file" condition (Ctrl+D).
- Support simple command lines with no advanced features like semicolons, pipes, redirections, or arguments.
- Find executables in the system and print an error message if not found.
- Implement the exit built-in command to exit the shell.
- Implement the env built-in command to print the current environment.
- Implement the cd built-in command to change the current directory.
- Support the cd - command to switch between the current and previous directories.
- Update the PWD environment variable when changing directories.
- Handle commands separated by ;.
- Support logical operators && and ||.
- Implement the alias built-in command to define and print aliases.
- Handle variable replacement.
- Support the $? variable to access the exit status of the last command.
- Support the $$ variable to access the current process ID.
- Ignore comments prefixed with #.
- Accept a command file as a command line argument. Execute the commands in the file and exit without printing a prompt.

## Built-in Commands

The shell interpreter provides the following built-in commands:

- **exit**: Exit the shell.

```
$ exit
```

You can optionally provide an integer status to exit with a specific status code.

```
$ exit 0
```

- **env**: Print the current environment.

```
$ env
```

- **cd**: Change the current directory.

```
$ cd [DIRECTORY]
```

If no directory is provided, the command is interpreted as cd $HOME. The `-` argument can be used to switch between the current and previous directories.

- **setenv**: Initializes a new environment variable or modifies an existing one.

```
$ setenv [VARIABLE] [VALUE]
```

- **unsetenv**: Remove an environment variable.

```
$ unsetenv [VARIABLE]
```

- **alias**: Allows you to define, print, or modify aliases.
  To print a list of all aliases:

```
$ alias
```

To print specific aliases:

```
$ alias [NAME]...
```

To define an alias:

```
$ alias [NAME]=[VALUE] [...]
```

To remove an alias:

```
$ unalias [NAME]...
```

## Command Line Arguments

The shell interpreter supports running commands from a file by providing the filename as a command line argument. The file should contain one command per line.

```
$ simple_shell [FILE]
```

In this mode, the shell does not display a prompt and does not read from standard input. Instead, it executes the commands in the file and exits.

## Contributors

- **Girma Eshete**
- [**Toby Salau**](https://github.com/Toby2507)
