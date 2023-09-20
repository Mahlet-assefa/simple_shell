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
	char **new_environ;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
				free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[i], environment[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
 * free_environ - Frees the the environment copy.
 */
void free_environ(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
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
			return (&environ[i]);
	}

	return (NULL);
}
