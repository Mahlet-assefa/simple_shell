#include "main.h"

char **_copy_environ(void);
void free_environ(void);
char **_getenv(const char *var);

/**
 * _copy_environ - Creates a copy of the environment.
 * Return: If an error occurs - NULL, O/w - a double pointer to the new copy.
 */
char **_copy_environ(void)
{
	char **new_environment;
	size_t s;
	int i;

	for (s = 0; new_environment[s]; s++)
		;

	new_environment = malloc(sizeof(char *) * (s + 1));
	if (!new_environment)
		return (NULL);

	for (i = 0; new_environment[i]; i++)
	{
		new_environment[i] = malloc(_strlen(environment[i]) + 1);

		if (!new_environment[i])
		{
			for (i--; i >= 0; i--)
				free(new_environment[i]);
			free(new_environment);
			return (NULL);
		}
		_strcpy(new_environment[i], environment[i]);
	}
	new_environment[i] = NULL;

	return (new_environment);
}

/**
 * free_environ - Frees the the environment copy.
 */
void free_environ(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environment);
}

/**
 * _get_env - this function gets an environmental variable from the PATH.
 * @var: The name of the environmental variable.
 * Return: If the environmental variable does not exist - NULL, otherwise- a pointer to the environmental variable.
 */
char **_get_env(const char *var)
{
	int i, len;

	len = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
			return (&environment[i]);
	}

	return (NULL);
}
