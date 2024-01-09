/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:56:42 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/16 18:10:50 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include <signal.h>
#include "builtins.h"

void		free_array(char **arr);

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

t_file_type	get_file_type(char *file)
{
	struct stat	buffer;

	if (stat(file, &buffer) == 0)
	{
		if (S_ISDIR(buffer.st_mode))
			return (T_DIRECTORY);
		else if (S_ISREG(buffer.st_mode))
			return (T_FILE);
	}
	return (T_ERROR);
}

static char	*transform_path(char *path, char *exec_path)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(path, "/");
	s2 = ft_strjoin(s1, exec_path);
	free(s1);
	return (s2);
}

char	*search_path(char *exec_path)
{
	char	*path;
	char	**toks;
	char	*ret;
	int		i;
	char	*tmp;

	ret = NULL;
	path = get_env("PATH");
	if (path != NULL)
	{
		i = -1;
		toks = ft_split(path, ':');
		while (toks && !ret && toks[++i])
		{
			tmp = transform_path(toks[i], exec_path);
			if (get_file_type(tmp) == T_FILE)
				ret = ft_strdup(tmp);
			free(tmp);
		}
		if (toks)
			free_array(toks);
	}
	if (!ret)
		return (cmd_error(exec_path));
	return (ret);
}

char	*find_executable(t_cmd	*cmd)
{
	t_file_type	type;
	char		*exec_path;

	if (!cmd->argv || !cmd->argv[0] || is_builtin(cmd))
		return (NULL);
	exec_path = cmd->argv[0];
	if (*exec_path == '.' || *exec_path == '/')
	{
		type = get_file_type(exec_path);
		if (type == T_DIRECTORY)
			return (is_directory_error(exec_path));
		else if (type == T_ERROR)
		{
			cmd_error(exec_path);
			return (NULL);
		}
		return (ft_strdup(exec_path));
	}
	return (search_path(exec_path));
}
