/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:53:41 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 16:36:48 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parsing.h"

void	assign_starts(char **start, char **cmd_start, char *str);
void	init_variables(t_cmd **cmd, t_cmd **first, char **start, char **c);
int		is_valid_sep_token(char c);
int		handle_redir_quotes(t_cmd *cmd, char **str, char **start);
void	check_arg_before_redir(t_cmd *cmd, char *str, char **start);

void	push_arg(t_cmd *cmd, char *str, char **start, int assign)
{
	char	*arg;

	if (!(*start))
		return ;
	arg = process_arg(ft_substr(*start, 0, str - *start), 0);
	if (arg)
		cmd->argv = reallocate_and_push(cmd->argv, arg, cmd->argc++);
	if (assign)
		*start = NULL;
}

int	try_push(t_cmd *cmd, char **start, char *str)
{
	if (*start && (str - *start) > 0)
		push_arg(cmd, str, start, 0);
	return (1);
}

int	register_cmd(t_cmd *first, t_cmd **cmd, char **start, char **cmd_start)
{
	t_cmd	*tmp;

	if ((is_valid_sep_token(**start) && (*start - *cmd_start) == 0)
		|| !*(*start + 1))
	{
		ft_putstr_fd("-minishell: syntax error\n", 2);
		return (0);
	}
	if (**start == '|')
		(*cmd)->type = PIPE;
	tmp = first;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = *cmd;
	(*cmd)->next = new_command();
	*cmd = (*cmd)->next;
	*start = NULL;
	*cmd_start = NULL;
	return (1);
}

int	check_escape_quotes(char **str)
{
	char	*s;
	int		doubleq;
	char	*start;

	s = *str;
	if (*s == '"' || *s == '\'')
	{
		start = s;
		doubleq = *s == '"';
		s = ft_strchr(s + 1, *s);
		while (BACKSLASH_ESCAPE && doubleq && s
			&& char_bckw(s, start, '\\') % 2 != 0)
			s = ft_strchr(s + 1, '"');
		if (s == NULL)
		{
			ft_putstr_fd("invalid quotes\n", STDERR_FD);
			return (0);
		}
	}
	else if (BACKSLASH_ESCAPE && *s == '\\')
		s++;
	*str = s;
	return (1);
}

t_cmd	*parse_rl(char *str)
{
	char	*start;
	t_cmd	*cmd;
	t_cmd	*first;
	char	*cmd_start;

	init_variables(&cmd, &first, &start, &cmd_start);
	while (*str)
	{
		if (*str != ' ')
		{
			assign_starts(&start, &cmd_start, str);
			if (!handle_redir_quotes(cmd, &str, &start) || (*str == '|'
					&& try_push(cmd, &start, str)
					&& !register_cmd(first, &cmd, &start, &cmd_start)))
				return (null_and_free(first));
			check_arg_before_redir(cmd, str, &start);
		}
		else if (start && (str - start) > 0)
			push_arg(cmd, str, &start, 1);
		if (*str && *str != '<' && *str != '>')
			str++;
	}
	try_push(cmd, &start, str);
	return (first);
}
