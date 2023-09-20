#include "main.h"

char **_copy_env(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copy_env - Creates a copy of the environ
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copy_env(void)
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
		_strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _get_env - a function to get an environmental variable from PATH.
 * @var: stores the name of environment 
 * Return: If the environmental variable does not exist - NULL other wise a pointer to the environmental variable name.
 */
char **_get_env(const char *var)
{
	int i, length;

	length = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], length) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
