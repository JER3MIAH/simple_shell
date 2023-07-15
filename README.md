A simple shell project created by Jeremiah and Hafsorh



#steps
1.) prompt the user <prompt.c>
2.) read input from the user(getline())  <read.c>
3.) Create an infinite loop to continue prompting the user   <main.c>
3.) handle the “end of file” condition(Ctrl+D exits the shell) <read.c>
3.) parse(tokenize) the user input(strtok())   <token.c>
4.) Execute commands (execve)   <execute.c>
5.) Handle the path   <path.c>
