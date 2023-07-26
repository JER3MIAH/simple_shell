#ifndef MAIN_H
#define MAIN_H

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

/*Function prototypes*/
void display_prompt(void);
char *read_cmd(void);
char **tokenize_cmd(char *cmd);
void execute_cmd(char *cmd);
char *cmd_path(char *cmd);
void get_environment(void);
void execute_cd(char *dir);
void execute_external_cmd(char **argv);
void free_argv(char **argv);
int execute_builtin_cmd(char **argv);
extern char **environ;
char *concat_paths(const char *path1, const char *path2);

#endif
