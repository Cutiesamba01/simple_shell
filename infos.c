#include "shell.h"

/**
 * set_info - initialises the info_t struct
 * @info: struct adr
 * @av: arg vector
 */

void set_info(info_t *info, char **av)
{
	int f = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (f = 0; info->argc && info->argv[f]; f++)
			;
		info->argc = f;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * clear_info - initialises the info_t struct
 * @info: struct adr
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_info - frees the info_t struct fields
 * @info: struct adr
 * @all: this is true when freeing all fields
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
