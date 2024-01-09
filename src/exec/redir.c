/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:22:58 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 14:41:23 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "exec.h"
#include "libft.h"

void	save_restore_fds(int restore);

t_redirection	**push_heredoc(t_redirection **heredocs, t_redirection *redir,
int count)
{
	t_redirection	**new;
	int				i;

	i = -1;
	new = (t_redirection **)malloc(sizeof(t_redirection *) * (count + 2));
	while (++i < count && heredocs)
		new[i] = heredocs[i];
	new[i] = redir;
	new[i + 1] = NULL;
	if (heredocs)
		free(heredocs);
	return (new);
}

t_redirection	**get_heredocs(t_cmd *cmd)
{
	t_redirection	**heredocs;
	t_redirection	*tmp;
	int				count;

	count = 0;
	heredocs = NULL;
	while (cmd)
	{
		tmp = cmd->in_redir;
		while (tmp)
		{
			if (tmp->type == REDIR_HEREDOC)
				heredocs = push_heredoc(heredocs, tmp, count++);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (heredocs);
}

int	handle_heredocs(t_cmd *cmd)
{
	t_redirection	**heredocs;
	int				i;
	char			*file;
	char			*tmp;
	int				r;

	r = -1;
	heredocs = get_heredocs(cmd);
	if (heredocs)
	{
		save_restore_fds(0);
		i = -1;
		while (r == -1 && heredocs[++i] != NULL)
		{
			tmp = ft_itoa(i);
			file = ft_strjoin(HEREDOC_PREFIX, tmp);
			free(tmp);
			r = heredoc(heredocs[i], file);
		}
		save_restore_fds(1);
		free(heredocs);
	}
	return (r);
}

int	handle_stdin(t_redirection *r, int *fd)
{
	if (!r->str)
		return (ambigous_redir_err());
	*fd = open(r->str, O_RDONLY);
	if (*fd < 0)
		return (perror_null());
	if (r->next)
	{
		if (*fd > -1)
			close(*fd);
		return (handle_stdin(r->next, fd));
	}
	return (*fd);
}

int	handle_stdout(t_redirection *r, int *fd)
{
	int		flags;

	if (!r->str)
		return (ambigous_redir_err());
	flags = O_CREAT | O_RDWR | O_TRUNC;
	if (r->type == REDIR_STDOUT_APPEND)
		flags = O_CREAT | O_RDWR | O_APPEND;
	*fd = open(r->str, flags, S_IRUSR | S_IWUSR);
	if (*fd < 0)
		return (perror_null());
	if (r->next)
	{
		if (*fd > -1)
			close(*fd);
		return (handle_stdout(r->next, fd));
	}
	return (*fd);
}
