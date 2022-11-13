#include "main.h"

/**
 *_execute - execute the builin commands and the stdin
 *@argv: pointer to the argv containings the array of tokens from
 * the tokenize function
 * @builtin_arr: pointer to the struct with the commands and their functions
 *
 * Return: 1 (flag) on success.
 */

int _execute(char **argv, builtin builtin_arr[])
{
	int i = 0;
	
	if (argv[0] == NULL)
	{
		return (1);
	}
	
	while (i < 5)
	{
		if (strcmp(argv[0], builtin_arr[i].command) == 0)
		{
			return(builtin_arr[i].func(argv));
		}
		i++;
	}
	
	return (shell_launch(argv));	
}
/*
 * shell_launch - creates a process to execute the commands
 * @argv: pointer to the argument
 *
 * Return: 1 on success
 */

int shell_launch(char **argv)
{
	int pid, existence, current_path = 0, c, status;
	char **path = 0, *command = 0, *path_command = 0, *env = 0;

	pid = fork();

	if (pid == 0)
	{
		env = getenv("PATH");
		if (env && env[0] == ':')
		{
			current_path = 1;
		}
		path = tokenize(env, ":");
		for (c = 0; path[c]; c++)
		{
			command = strcat("/", argv[0]);
			path_command = strcat(path[c], command);
			existence = check_existence(path_command);
			if (existence != -1 && !current_path)
			{
				argv[0] = path_command;
				break;
			}
			else
			{
				free(path_command);
			}
			free(command);
		}
		existence = check_existence(argv[0]);

		if (existence == -1)
		{
			_freeall(argv, path);
		}
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("ERROR\n");
		}
		_freeall(argv, path);
	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else 
	{
		wait(&status);
	}
	return (WEXITSTATUS(status));
}
/**
 * _freeall - frees arv and path
 * @agv: buffer containig the tokens
 * @path: the path to look for the exec files
 */
void _freeall(char **argv, char **path)
{

	free(argv[0]);
	free(argv);
	free(path);
	exit (127);
}
/**
 * check_existence - check whether a file exists
 * @path: pointer to the path to search in
 *
 * Return: 1 on success and -1 if failed
 */
int check_existence(char *path)
{
	int fd = access(path, F_OK | X_OK);

	if (fd == -1)
	{
		return (-1);
	}
	return (-1);
}



