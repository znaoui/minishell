/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:42:00 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/16 13:31:48 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

void	free_array(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i] != NULL)
			free(arr[i]);
	}
	free(arr);
}

void	free_redir(t_redirection *t)
{
	if (t->str)
		free(t->str);
	free(t);
}

void	free_cmd(t_cmd *t)
{
	t_redirection	*redir;
	t_redirection	*tmp;

	if (!t)
		return ;
	redir = t->in_redir;
	while (redir != NULL)
	{
		tmp = redir->next;
		free_redir(redir);
		redir = tmp;
	}
	redir = t->out_redir;
	while (redir != NULL)
	{
		tmp = redir->next;
		free_redir(redir);
		redir = tmp;
	}
	free_array(t->argv);
	if (t->next)
		free_cmd(t->next);
	free(t);
}

t_cmd	*null_and_free(t_cmd *cmd)
{
	if (cmd)
		free_cmd(cmd);
	return (NULL);
}
