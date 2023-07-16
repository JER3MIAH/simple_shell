#ifndef MAIN_H
#define MAIN_H

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*Function prototypes*/
void display_prompt(void);
char *read_cmd(void);
char **tokenize_cmd(char *cmd);
void execute_cmd(char *cmd);

#endif
