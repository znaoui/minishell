/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:08:57 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/02 01:04:08 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:05:11 by cdudzik           #+#    #+#             */
/*   Updated: 2022/10/28 18:21:34 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_type_to_str(t_cmd_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == CMD)
		return ("CMD");
	return ("UNKNOWN");
}

char	*redir_type_to_str(t_redir_type type)
{
	if (type == REDIR_STDOUT)
		return ("STDOUT");
	else if (type == REDIR_STDOUT_APPEND)
		return ("STDOUT_APPEND");
	else if (type == REDIR_STDIN)
		return ("STDIN");
	else if (type == REDIR_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	dump_arr(char **arr)
{
	char	*str;
	int		i;

	if (arr)
	{
		i = 0;
		str = arr[i];
		while (str != NULL)
		{
			printf("[%d] %s\n", i, str);
			str = arr[++i];
		}
	}
}

void	dump_redir(t_redirection *redir, int out)
{
	while (redir != NULL)
	{
		if (out)
			printf("\n****** STD OUT REDIR ******\n");
		else
			printf("\n****** STD IN REDIR ******\n");
		printf("TYPE: %s\n", redir_type_to_str(redir->type));
		printf("FILE: %s\n", redir->str);
		printf("********************\n");
		redir = redir->next;
	}
}

void	dump_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	printf("-------------- CMD DUMP -------------\n");
	printf("TYPE: %s\n", cmd_type_to_str(cmd->type));
	printf("ARGV:\n");
	dump_arr(cmd->argv);
	dump_redir(cmd->in_redir, 0);
	dump_redir(cmd->out_redir, 1);
	printf ("-------------------------------------\n");
	if (cmd->next)
		dump_cmd(cmd->next);
}
