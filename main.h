#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global Environemnt */
extern char **environment;

/* Global Program Name */
char *name;

/* Global History Counter */
int hist;

/**
 * struct lists_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct lists_s
{
	char *dir;
	struct lists_s *next;
} lists_t;

/**
 * struct builtins_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtins_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtins_t;

/* Main Helpers */
char *get_location(char *command);
lists_t *get_path_dir(char *path);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void free_list(lists_t *head);


/* Builtin Helpers */
char **_copy_environ(void);
void free_environ(void);
char **_get_env(const char *var);

/* Builtins */
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int (*get_builtin(char *command))(char **args, char **front);
int shellie_exit(char **args, char **front);
int shellie_cd(char **args, char __attribute__((__unused__)) **front);
int shellie_help(char **args, char __attribute__((__unused__)) **front);

/*tokenizer*/
int lentoken(char *str, char *delim);
int tokencounter(char *str, char *delim);
char **_strtok(char *line, char *delim);
#endif
