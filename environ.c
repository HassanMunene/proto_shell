#include "main.h"

/**
 * _printenv - prints the environment
 * @argv: pointer to the commands 
 *
 * Return: 1 on success
 */

int _printenv(char **argv)
{
	int i;
	(void) argv;

	for(i = 0; *environ[i] != '\0'; i++)
	{
		puts(environ[i]);
		printf("\n");
	}
	return (0);
}

/**
 * _setenv - set a new environmental variable
 * @argv: pointer to the input commmand
 *
 * Return: 1 on success
 */
int _setenv(char **argv)
{
	int status = EXIT_SUCCESS;
	int exist = 0;
	int i = 0;
	char *dup = 0;
	char *tok = 0;
	char *val = 0;

	while (environ[i])
	{
		dup = strdup(environ[i]);
		tok = strtok(dup, "=");

		if (!strcmp(tok, argv[1]))
		{
			tok = strcat(argv[1], "=");
			val = strcat(tok, argv[2]);

			environ[i] = strcpy(environ[i], val);
			free(tok);
			free(val);
			exist = 1;
		}
		free(dup);
		i++;
	}
	return (status);
}

/**
 * _unsetenv - unset an environmental var
 * @argv: pointer to the buffer with the command
 *
 * Return: 1 on success
 */
int _unsetenv(char **argv)
{
	int i = 0, exist = 0, len = 0, j = 0;
	char *tok, *copy;
	char **new_env;

	while (environ[i])
	{
		copy = strdup(environ[i]);
		tok = strtok(copy, "=");

		if (!strcmp(tok, argv[i]))
		{
			exist = 1;
		}
		len++;
		i++;
		free(copy);
	}

	if (exist)
	{
		new_env = malloc(sizeof(char *) * (len - 1));
		for (i = 0; i < len; i++)
		{
			copy = strdup(environ[i]);
			tok = strtok(copy, "=");
			if (!strcmp(tok, argv[i]))
			{
				printf("Remove : %s\n", environ[i]);
				continue;
			}
			new_env[j] = environ[i];
			j++;
		}
		new_env[len - 1] = NULL;
		environ = new_env;
	}
	return (1);
}






