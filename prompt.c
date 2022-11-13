#include "main.h"
/**
 * main - this is the main function that integrates all other functions
 * since this is where the main shell is called from
 *
 * Return: 0 on sucess
 */

int main(void)
{
	char *buffer;
	char **argv = NULL;
	int flag = 1;
	int error_count = 0;
	int status = EXIT_SUCCESS;

	builtin builtin_arr[] = 
	{
		{"exit", ourexit},
		{"env", _printenv},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{NULL, NULL}
	};

	/*if (isatty(STDIN_FILENO) != 1)
	{
		_non_int(builtin_arr);	
	} 
	(void)signal(SIGINT, sign_handler);
	(void)builtin_arr;*/

	while (flag)
	{
		printf("$ ");

		error_count++;
		buffer = read_line();
		argv = tokenize(buffer, " \t\n\r\a");
		status = _execute(argv, builtin_arr);

		free(argv);
		free(buffer);
	}
	return (status); /*this is because status is equal to EXIT_SUCCESS*/ 
}

/**
 * read_line - read input from stdin
 *
 * Return: a pointer to the buffer read from stdin
 */
char *read_line()
{
	char *buffer = NULL;
	size_t buffersize = 0;

	if (getline(&buffer, &buffersize, stdin) == EOF)
	{
		printf("\n");
		free(buffer);
		exit(EXIT_SUCCESS); 
	}
	buffer[strlen(buffer) - 1] = '\0';
	return (buffer);
}

/**
 * tokenize - split the buffer received from getline
 * into tokens that can be now executed
 * @delim:  the delimeter chosen
 * @buffer: the pointer to the buffer
 *
 * Return: a pointer to the arrays of the tokens
 */
char **tokenize(char *buffer, char *delim)
{
	int buffersize = 80;
	int i = 0;
	char **tokens = malloc (sizeof(char *) * buffersize);
	char *token;

	if (!tokens)
	{
		perror("Memory not allocated\n");
		free(buffer);
		exit(EXIT_FAILURE); 
	}
	token = strtok(buffer, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
/**
 * sign_handler - handles the absence of a sign
 * @sig: integer
 *
 */
void sign_handler(int sig)
{
	(void) sig;
	printf("\n");
	printf("$ ");
	fflush(stdout);
}
















