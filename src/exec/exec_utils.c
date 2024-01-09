/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:17:52 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 16:52:43 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	cmd_next(t_cmd *cmd, t_exec_context *ctx)
{
	int	fd;

	close(ctx->pipe_fd[0]);
	if (!cmd->next->argc || !cmd->next->argv[0])
	{
		fd = open("/dev/null", O_RDWR);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(ctx->pipe_fd[1], STDOUT_FILENO);
	close(ctx->pipe_fd[1]);
}

void	dup_all(t_cmd *cmd, t_exec_context *ctx)
{
	if (ctx->out_fd > 0)
	{
		dup2(ctx->out_fd, STDOUT_FILENO);
		close(ctx->out_fd);
	}
	else if (cmd->next)
		cmd_next(cmd, ctx);
	if (ctx->in_fd > 0)
	{
		dup2(ctx->in_fd, STDIN_FILENO);
		close(ctx->in_fd);
	}
	else if (ctx->prev_read != STDIN_FILENO)
	{
		dup2(ctx->prev_read, STDIN_FILENO);
		close(ctx->prev_read);
	}
}

pid_t	*get_pids(t_cmd *first)
{
	int		cmds;
	pid_t	*pids;

	cmds = 0;
	while (first != NULL && ++cmds)
		first = first->next;
	pids = (pid_t *)malloc(sizeof(pid_t) * cmds);
	return (pids);
}

t_exec_context	get_ctx(t_cmd *cmd, int prev_read)
{
	t_exec_context	ctx;

	g_config.cmd_is_running = 1;
	if (!cmd)
		ctx.path = NULL;
	else
		ctx.path = find_executable(cmd);
	ctx.in_fd = 0;
	ctx.out_fd = 0;
	ctx.prev_read = prev_read;
	ctx.has_pipe = 0;
	ctx.ret = 0;
	ctx.is_child = 0;
	return (ctx);
}

int	free_mem(t_cmd *cmd, pid_t *pid, t_exec_context *ctx, int end)
{
	if (ctx->path)
		free(ctx->path);
	ctx->path = NULL;
	if (ctx->prev_read)
		close(ctx->prev_read);
	if (end)
	{
		if (pid)
			free(pid);
		if (ctx->in_fd > 0)
			close(ctx->in_fd);
		if (ctx->out_fd > 0)
			close(ctx->out_fd);
		g_config.cmd_is_running = 0;
	}
	else if (cmd->next && ctx->has_pipe)
	{
		ctx->prev_read = ctx->pipe_fd[0];
		close(ctx->pipe_fd[1]);
	}
	return (1);
}
