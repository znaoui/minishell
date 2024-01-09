/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:40:07 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/02 01:44:00 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parsing.h"

t_redir_type	get_redir_type(char *str)
{
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (REDIR_STDOUT_APPEND);
		return (REDIR_STDOUT);
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (REDIR_HEREDOC);
		return (REDIR_STDIN);
	}
	return (REDIR_UNKNOWN);
}

int	is_valid_sep_token(char c)
{
	return (c == '>' || c == '<' || c == '|' || !c);
}

char	*get_next_word(char *str, char **og)
{
	char	*start;

	start = NULL;
	while (!is_valid_sep_token(*str))
	{
		if (*str != ' ' && !start)
			start = str;
		if (start && *str == ' ')
			break ;
		str++;
	}
	if (!start || (str - start) == 0)
	{
		ft_putstr_fd("-minishell: syntax error\n", 2);
		return (NULL);
	}
	*og = str;
	return (ft_substr(start, 0, str - start));
}

void	assign_redir(t_cmd *cmd, t_redirection *redir)
{
	t_redirection	*tmp;

	if (redir->type == REDIR_HEREDOC || redir->type == REDIR_STDIN)
	{
		tmp = cmd->in_redir;
		if (!tmp)
			cmd->in_redir = redir;
		else
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = redir;
		}
		return ;
	}
	tmp = cmd->out_redir;
	if (!tmp)
		cmd->out_redir = redir;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	handle_redir(t_cmd *cmd, char **str, char **start)
{
	t_redirection	*redir;
	t_redir_type	type;
	char			*s;

	s = *str;
	type = get_redir_type(s);
	s += 1 + (type == REDIR_STDOUT_APPEND || type == REDIR_HEREDOC);
	s = get_next_word(s, str);
	if (!s)
		return (0);
	s = process_arg(s, type == REDIR_HEREDOC);
	while (cmd->next != NULL)
		cmd = cmd->next;
	redir = (t_redirection *)malloc(sizeof(t_redirection));
	redir->type = type;
	redir->str = s;
	redir->next = NULL;
	assign_redir(cmd, redir);
	*start = NULL;
	return (1);
}
