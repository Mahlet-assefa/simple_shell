#include "main.h"

char *fill_path_dir(char *path);
lists_t *get_path_dir(char *path);

/**
 * get_location - Finds the full pathname of a command in the PATH
 *		environment variable.
 * @command: The command to find.
 * Return: The full pathname of the command if it is found in the PATH
 *	environment variable, or NULL otherwise.
 */
char *get_location(char *command)
{
	char **path, *a;
	lists_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		a = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!a)
			return (NULL);

		_strcpy(a, dirs->dir);
		_strcat(a, "/");
		_strcat(a, command);

		if (stat(a, &st) == 0)
		{
			free_list(head);
			return (a);
		}

		dirs = dirs->next;
		free(a);
	}

	free_list(head);

	return (NULL);
}
/**
 * fill_path_dir - Copies a colon-separated list of directories, replacing
 *		any leading, sandwiched, or trailing colons (:) with
 *		the current working directory.
 * @path: The colon-separated list of directories.
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i, l = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				l += _strlen(pwd) + 1;
			else
				l++;
		}
		else
			l++;
	}
	path_copy = malloc(sizeof(char) * (l + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Splits a colon-separated list of directories into
 *                a linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
lists_t *get_path_dir(char *path)
{
	int ind;
	char **d, *path_copy;
	lists_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	d = _strtok(path_copy, ":");
	free(path_copy);
	if (!d)
		return (NULL);

	for (ind = 0; d[ind]; ind++)
	{
		if (add_node_end(&head, d[ind]) == NULL)
		{
			free_list(head);
			free(d);
			return (NULL);
		}
	}

	free(d);

	return (head);
}
