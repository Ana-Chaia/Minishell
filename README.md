# Minishell
**As beautiful as a shell**

**Introduction**

Minishell is a project aimed at developing a minimal shell that simulates basic functionalities of bash. This educational exercise helps in understanding processes, file descriptors, and the mechanics of command-line interpreters. With Minishell, you can explore shell programming and foundational operating system concepts.

**Features - Core Functionalities**

Prompt: Displays a prompt while waiting for user input.
Command Execution: Executes commands based on the $PATH or given relative/absolute paths.

**Quoting Rules:**

Single quotes (') prevent interpretation of meta-characters.
Double quotes (") prevent interpretation except for $ (used for variable expansion).

**Redirections:**

"<" : Input redirection.
">" : Output redirection.
"<<" : Heredoc, reading input until a specified delimiter is encountered.
">>" : Append mode for output redirection.

**Pipes:**

Implements pipes (|) to connect commands.
Environment Variables: Handles $VAR for environment expansion.

**Special Variables:**

$?: Provides the exit status of the last executed command.

**Built-in Commands:**

echo (supports -n flag).
cd (supports relative and absolute paths).
pwd.
export.
unset.
env.
exit.

**Interactive Features**

Ctrl+C: Interrupts the current command and displays a new prompt.
Ctrl+D: Exits the shell.
Ctrl+\: Does nothing, like in bash.

**Memory Management**

No memory leaks allowed in custom code.
The readline() function's known leaks are acceptable.

**Skills**

Proficiency in C programming.
Understanding of process management, file descriptors, and signals.
Familiarity with Makefiles and memory management in C.
Knowledge of bash behavior for feature comparison.

**Installation**

git clone <repository_url>
cd minishell
make
./minishell

**Acknowledgments**

Special thanks to the 42 Network for designing the Minishell project and the community for providing valuable resources.

