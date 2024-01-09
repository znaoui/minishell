/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:02:23 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 14:45:58 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "builtins.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->argv)
		return (0);
	return (!ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "env")
		|| !ft_strcmp(cmd->argv[0], "pwd")
		|| !ft_strcmp(cmd->argv[0], "export")
		|| !ft_strcmp(cmd->argv[0], "exit")
		|| !ft_strcmp(cmd->argv[0], "echo")
		|| !ft_strcmp(cmd->argv[0], "unset"));
}

int	handle_builtin(t_cmd *cmd)
{
	int	code;
	int	ret;

	code = 0;
	if (!ft_strcmp(cmd->argv[0], "cd"))
		code = main_cd(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "env"))
		code = main_env(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		code = main_pwd(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		code = main_exit(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "export"))
		code = main_export(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		code = main_unset(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		code = main_echo(cmd->argc, cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "exit") && g_config.exit_code != -1)
		ret = 1;
	else
		ret = -1;
	g_config.exit_code = code;
	return (ret);
}
