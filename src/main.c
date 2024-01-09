/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:05:22 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/16 19:37:19 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include <unistd.h>

t_minishell_config	g_config;
int					array_size(char **arr);
int					has_str_starts_with(char **arr, char *str, int size);
char				*current_directory(void);

char	*new_pwd(void)
{
	char	*cwd;
	char	*str;

	cwd = current_directory();
	if (!cwd)
		return (NULL);
	str = ft_strjoin("PWD=", cwd);
	free(cwd);
	return (str);
}

int	initialize(char **envp)
{
	int		size;
	int		has_pwd;

	if (!RUNNING_TESTS && !isatty(STDIN_FD))
	{
		ft_putstr_fd("-minishell: input files are not allowed\n", 2);
		return (0);
	}
	register_signals();
	register_caps();
	g_config.exit_code = 0;
	g_config.cmd_is_running = 0;
	size = array_size(envp) + 1;
	has_pwd = has_str_starts_with(envp, "PWD=", size);
	size += !has_pwd;
	g_config.env = (char **)malloc(sizeof(char *) * size);
	g_config.env[--size] = NULL;
	if (!has_pwd)
		g_config.env[--size] = new_pwd();
	while (size--)
		g_config.env[size] = ft_strdup(envp[size]);
	g_config.pwd_cache = ft_strdup(get_env("PWD"));
	return (1);
}

int	process_cmd(t_cmd *cmd)
{
	int	r;

	r = -1;
	if (cmd)
	{
		if (DEBUG)
			dump_cmd(cmd);
		r = exec_cmd(cmd);
		free_cmd(cmd);
	}
	return (r);
}

void	cleanup(void)
{
	if (g_config.pwd_cache)
		free(g_config.pwd_cache);
	free_array(g_config.env);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_cmd		*cmd;
	int			r;

	(void)argv;
	r = -1;
	if (!initialize(envp))
		return (0);
	while (argc == 1 && r < 0)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			cmd = parse_rl(line);
			r = process_cmd(cmd);
		}
		free(line);
	}
	r = g_config.exit_code;
	cleanup();
	return (r);
}
