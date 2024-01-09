/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:23:38 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 15:25:55 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <unistd.h>
#include "builtins.h"

void	restore_fds(int in, int out)
{
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
}

int	exec_builtin_nopipe(t_cmd *cmd, t_exec_context *ctx)
{
	int	r;
	int	saved_out;
	int	saved_in;

	saved_out = -1;
	saved_in = -1;
	if (ctx->out_fd > 0)
	{
		saved_out = dup(STDOUT_FILENO);
		dup2(ctx->out_fd, STDOUT_FILENO);
		close(ctx->out_fd);
	}
	if (ctx->in_fd > 0)
	{
		saved_in = dup(STDIN_FILENO);
		dup2(ctx->in_fd, STDIN_FILENO);
		close(ctx->in_fd);
	}
	r = handle_builtin(cmd);
	restore_fds(saved_in, saved_out);
	return (r);
}
