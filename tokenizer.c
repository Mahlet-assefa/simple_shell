#include "main.h"

int lentoken(char *str, char *delim);
int tokencounter(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * lentoken - Finds the index of the delimiter marking the end of
 *	the first token in a string.
 * @str: The string that is searched.
 * @delim: The delimiter character.
 * Return: The index of the delimiter marking the end of the first
 *	token in the string.
 */
int lentoken(char *str, char *delim)
{
	int index = 0, l = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		l++;
		index++;
	}

	return (len);
}

/**
 * tokencounter - Counts the number of delimited
 *                words in a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words in the str.
 */
int tokencounter(char *str, char *delim)
{
	int index, tokens = 0, l = 0;

	for (index = 0; *(str + index); index++)
		l++;

	for (index = 0; index < l; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += lentoken(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Splits the string into words.
 * @line: The input string.
 * @delim: the delimiter.
 * Return: A pointer to an array of strings.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = tokencounter(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = lentoken(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
