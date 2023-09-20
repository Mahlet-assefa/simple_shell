#include "main.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shell_env - Prints the current environment.
 * @front: A double pointer to the beginning of args.
 * @args: An array of args passed to the shell.
 * Return: If an error occurs - -1, Otherwise - 0.
 * Description: Prints one variable per line
 */
int shell_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char c = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &c, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - Changes an environment variable to the PATH.
 * @front: A double pointer to the beginning of arguments.
 * @args: An array of args passed to the shell.
 * Description: args[1] is the name of the new or existing PATH var,
 *		args[2] is the val to set the new or changed variable to.
 *
 * Return: If an error occurs - -1, Otherwise - 0.
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_val;
	size_t size;
	int i;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_error(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_val);
		return (create_error(args, -1));
	}

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	free(environ);
	environ = new_environ;
	environ[i] = new_val;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - Deletes an environmental variable from the PATH.
 * @front: A double pointer to the beginning of args.
 * @args: An arr of args passed to the shell.
 * Description: args[1] is the PATH variable to remove.
 * Return: If an error occurs - -1, Otherwise - 0.
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int i, i2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (i = 0, i2 = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			continue;
		}
		new_environ[i2] = environ[i];
		i2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
