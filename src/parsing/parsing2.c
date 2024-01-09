/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:29:25 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 16:04:37 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int		check_escape_quotes(char **str);
void	push_arg(t_cmd *cmd, char *str, char **start, int assign);

void	check_arg_before_redir(t_cmd *cmd, char *str, char **start)
{
	if (*str && (*str + 1) && (*(str + 1) == '>' || *(str + 1) == '<')
		&& start)
		push_arg(cmd, str + 1, start, 1);
}

int	handle_redir_quotes(t_cmd *cmd, char **str, char **start)
{
	if (!check_escape_quotes(str) || ((**str == '>' || **str == '<')
			&& !handle_redir(cmd, str, start)))
		return (0);
	return (1);
}

void	assign_starts(char **start, char **cmd_start, char *str)
{
	if (!*start)
		*start = str;
	if (!*cmd_start)
		*cmd_start = str;
}

void	init_variables(t_cmd **cmd, t_cmd **first, char **start, char **c)
{
	*cmd = new_command();
	*first = *cmd;
	*start = NULL;
	*c = NULL;
}
