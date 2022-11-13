#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>


/**
 * struct builtin_t - this is a struct to handle the 
 * built in commands of the shell 
 * @command: the command to be inputed
 * @func: function pointer to execute the command
 *
 * Description: this struct has a command and a function pointer 
 * that will react to the command
 */
typedef struct builtin_t
{
	char *command;
	int (*func) (char **argv);
} builtin;

int ourexit(char **argv);
int _printenv(char **argv);
int _setenv(char **argv);
int _cd(char **argv);
int _unsetenv(char **argv);
void sign_handler(int sig);

void _non_int(builtin arr[]);

char **tokenize(char *buffer, char *delim);
char *read_line();
int shell_launch(char **argv);
int _execute(char **argv, builtin builtin_arr[]);
extern char **environ;
extern char *program_invocation_name;
void _freeall(char **argv, char **path);

int check_existence(char *file);
void _non_int(builtin arr[]);
#endif
