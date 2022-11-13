#include "main.h"

/**
 * ourexit - checks whether the input is the exit command
 * @argv: buffer with the commands
 *
 * Return: exit status
 */
int ourexit(char **argv)
{
	int status = 0;
	int i;

	if (argv[1] == NULL)
	{
		free(argv[0]);
		free(argv);
		fflush(stdout);
		exit(status);
	}

	for (i = 0; argv[1][i] != '\0'; i++)
	{
		if (argv[1][i] < 48 || argv[1][i] > 57)
		{
			return (2);
		}
	}
	status = atoi(argv[1]);
	free(argv[0]);
	free(argv);
	exit (status);
}

/**
 * _cd - function that changes the current directory
 * @argv: the sting containing the input
 *
 * Return: 1 on success
 */
int _cd(char **argv)
{
	char buffer[1024];
	char *cwd;
	char *new_wd;
	char *comp = "-";
	char *old_pwd;
	int chint = 0;
	char *env;

	cwd = getcwd(buffer, sizeof(buffer));
	if (argv[1] == NULL)
	{
		setenv("OLDPWD", getcwd(buffer, sizeof(buffer)), 1);
		env = getenv("HOME");
		chdir(env);
		return (0);
	}
	if (strcmp(argv[1], comp) == 0)
	{
		old_pwd = getenv("OLDPWD");
		setenv("OLDPWD", getcwd(buffer, sizeof(buffer)), 1);
		chdir(old_pwd);
		return (0);
	}
	if (cwd == NULL)
	{
		free(argv);
		perror("Error: ");
		return (1);
	}

	chint = chdir(argv[1]);
	if (chint == -1)
	{
		free(argv);
		perror("Error: ");
		return (1);
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	new_wd = getcwd(buffer, sizeof(buffer));
	setenv("PWD", new_wd, 1);
	return (0);
}
