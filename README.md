#INRODUCTION
===============

A simple shell project created by JEREMIAH OWOADE and ABDULLATEEF ADELUOLA HAFSORH. The simple shell is a collaborative project, the project is to create a shell that mimics the bash shell. The shell is command line interface(CLI) program that takes command from the user and give them to the operating system(OS) to perform.The shell project was completed with C programming language, it was complied with the gcc complier, and it was styled and documented with Betty style and documentation.

#SUMMARY
================

We created a shell command that prompt the user to type a command and read input from the user, an infinite loop was included in order to prompt the user  to type in more commands  (handle arguments) and an end of file condition which allow the user to exit the shell.
The user input was parsed and tokenized (Split or break down the command). The user input and out was handled and managed using the fork (A function that creates a new process) and execve (The function is used to execute the program and replaces the current process) function.

A function to get the PATH was created by declaring a variable to which we will assign the path obtained from the environment variables, using the getenv (A function that gets the value of a single or all environment variables) function to which we will assign the path obtained from the environment variables (PATH). A duplicate of the path was created using the strdup (A function that duplicates a string) function, and the return value was assigned to our variable which in our case is named the <path_copy>, we generated a path for the given command and length of the command was obtained using the strlen (A function takes a string as an argument and returns its length) function,
the variable <path_copy> to which our duplicate was assigned was splited using the strtok function andt was separated with a delimeter (:), another variable was created to hold the return value of the strtok (A function that splits or breaks down string into a series of tokens using the delimiter) which was named <token_path>.

A command to handle argument for built in exit was created using the atoi function (A function that coverts string to interger) to use an interger to exit the shell and also implemented an environment built in command that prints the current environment.
compilation was done with the gcc -wall-werror-wextra-pedantic-std, and was named hsh (filename). The hsh filename was invoked by compiling all the .c files and run the executable results. The hsh could be revoked interactively and non-interactively.

#CONCLUSION
======================

We learned and experienced how shell work, we also able to create, fork() and work with processes. Execute a program from one  program to another, handle memory allocation and memory leaks in the program.

About simple shell collaborative projects.
