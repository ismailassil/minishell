# Minishell

Minishell is a project developed as part of the curriculum at 1337School. The aim of this project is to create a small shell program that mimics the basic behavior of the Bash shell. This includes parsing and executing commands, handling environment variables, managing redirections, and implementing some built-in shell commands.

## Features

- **Command Execution**: Minishell can execute commands entered by the user, including external programs.
- **Builtin Commands**: Minishell supports a set of built-in commands such as `echo`, `cd`, `pwd`, `export`, `unset`, and `env`.
- **Redirections**: It can handle input/output redirections using `<` and `>` operators.
- **Pipelines**: Minishell supports command pipelines using the `|` operator.
- **Environment Variables**: It manages environment variables like `PATH` and supports expansion of variables.
- **Signals Handling**: Proper handling of signals like `Ctrl+C` and `Ctrl+\`.
- **Error Handling**: Minishell provides informative error messages for various scenarios to aid in debugging.
- **Quoting**: Properly handles quoting and escaping characters in commands.

## Getting Started

To get started with Minishell, follow these steps:

1. Clone the repository: `git clone https://github.com/ismailassil/minishell.git`
2. Navigate to the project directory: `cd minishell`
3. Build the project: `make`
4. Run the minishell: `./minishell`

## Usage

Once you have launched Minishell, you can start entering commands just like you would in a regular shell. Here are some examples of usage:

```bash
$ ls -l
$ cd /path/to/directory
$ echo "Hello, Minishell!"
$ export MY_VARIABLE=value
```

For a list of built-in commands and their usage, you can use the `help` command within Minishell.

## Contributing

Contributions to Minishell are welcome! If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request.

## Acknowledgements

Minishell was developed by students at 1337School as part of their curriculum. Special thanks to the instructors and staff for their guidance and support.
