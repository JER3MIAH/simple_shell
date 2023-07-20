#INTRODUCTION

A simple shell project created by JEREMIAH and HAFSORH. The simple shell is a collaborative project, the project is to create a shell that mimics the bash shell.
The shell project was written with C programming language, it was complied with the gcc complier, and it was styled and documented with Betty.

#SUMMARY

We created a shell command that prompt the user to type a command and read input of from the user. An infinite loop was included in order to prompt the user  to type in more commands and an end of file condition which allow the user to exit the shell.
The user input was parsed and tokenized (Split the command). The user input and out was handled and managed using the fork and execve function.

A function to get PATH was created by declaring a variable to which we will assign the path obtained from the environment variables, using the getenv function to which we will assign the path obtained from the environment variables (PATH). A duplicate of the path was created using the strdup (string duplicate) function, and the return value was assigned to our variable which in our case is named the <path_copy>, we generated a path for the given command and length of the command was obtained using the strlen (String length) function,
the variable <path_copy> to which our duplicate was assigned was splited using the strtok function andt was separated with a delimeter (:), another variable was created to hold the return value of the strtok which was named <token_path>.

A command to handle argument for built in exit was created using the atoi function (A function that coverts string to interger) to use an interger to exit the shell and also implemented an environment built in command that prints the current environment. 
