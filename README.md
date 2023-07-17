A simple shell project created by Jeremiah and Hafsorh



#steps
1.) prompt the user <prompt.c>
2.) read input from the user(getline())  <read.c>
3.) Create an infinite loop to continue prompting the user   <main.c>
4.) handle the “end of file” condition(Ctrl+D exits the shell) <read.c>
5.) parse(tokenize) the user input(strtok())   <token.c>
6.) Execute commands (execve)   <execute.c>
7.) Handle the path   <path.c>
{
    => create a function to get the path <cmd_path.c>
    => declare a variable to which we will assign the path obtained from the environment variables <path>
    => declare a variable to hold a copy of <path>
    => use <getenv> to search for the environment variable name which in our case is "PATH"
    => assign the return value of getenv() to our <path> variable
    => create a duplicate of the path using strdup and assign the return value to our <path_copy> variable
    ## Now we'll generate the path for the given command
    => Get the length of the given command[create a new variable<cmd_length> and use <strlen()> to get the lenght]
    => Break down the path_copy variable into tokens *ugh, strtok again...*
    => Anyways... we'll use the <strtok()> with ":" as our delimiter.
    => Then we also need a variable to hold the return value of strtok we'll call it <token_path>
    => *hmmm...i'm getting tired of typing all this and the next steps are a bit complicated so i'll just summarize.*
    => 
}
