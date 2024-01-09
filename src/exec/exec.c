/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:15:47 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 14:56:31 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "builtins.h"

int	run_child(t_cmd *cmd, pid_t *pids, t_exec_context *ctx, int builtin)
{
	int	code;

	ctx->is_child = 1;
	code = -1;
	reset_signals();
	dup_all(cmd, ctx);
	if (builtin && handle_builtin(cmd))
		code = g_config.exit_code;
	else
		execve(ctx->path, cmd->argv, g_config.env);
	free_mem(cmd, pids, ctx, 0);
	if (code == -1)
		return (perror_null());
	return (code);
}

int	get_new_ctx(t_cmd *cmd, pid_t *pids, t_exec_context *ctx)
{
	*ctx = get_ctx(cmd, ctx->prev_read);
	if ((cmd->in_redir && !handle_stdin(cmd->in_redir, &ctx->in_fd))
		|| (cmd->out_redir && !handle_stdout(cmd->out_redir, &ctx->out_fd)))
	{
		free_mem(cmd, pids, ctx, 0);
		return (1);
	}
	if (cmd->next && pipe(ctx->pipe_fd) < 0)
	{
		free_mem(cmd, pids, ctx, 1);
		return (perror_null());
	}
	else
		ctx->has_pipe = 1;
	return (1);
}

void	wait_all(t_cmd *cmd, pid_t *pids, t_exec_context *ctx, int pipes)
{
	pid_t	last;
	int		code;

	code = -1;
	if (!ctx->is_child && pipes)
	{
		last = pids[pipes - 1];
		while (pipes--)
		{
			if (pids[pipes] == last)
			{
				waitpid(pids[pipes], &code, 0);
				if (WIFEXITED(code))
					g_config.exit_code = WEXITSTATUS(code);
				else
					g_config.exit_code = 130;
			}
			else
				waitpid(pids[pipes], NULL, 0);
		}
	}
	free_mem(cmd, pids, ctx, 1);
}

int	fork_exec(t_cmd *cmd, pid_t *pids, t_exec_context *ctx, int *pipes)
{
	int	r;
	int	builtin;

	r = 1;
	builtin = is_builtin(cmd);
	if (builtin || ctx->path)
	{
		pids[*pipes] = fork();
		if (pids[*pipes] < 0)
			r = perror_null();
		else if (pids[*pipes] == 0)
		{
			ctx->ret = run_child(cmd, pids, ctx, builtin);
			return (0);
		}
		else
			(*pipes)++;
	}
	ctx->ret = r;
	return (r);
}

int	exec_cmd(t_cmd	*cmd)
{
	int				pipes;
	pid_t			*pids;
	t_exec_context	ctx;
	int				r;

	ctx = get_ctx(NULL, STDIN_FILENO);
	pipes = 0;
	r = handle_heredocs(cmd);
	pids = get_pids(cmd);
	while (r == -1 && cmd)
	{
		if (!get_new_ctx(cmd, pids, &ctx))
			return (-1);
		if (!cmd->next && !pipes && is_builtin(cmd))
			r = exec_builtin_nopipe(cmd, &ctx);
		else if (!fork_exec(cmd, pids, &ctx, &pipes))
			r = ctx.ret;
		free_mem(cmd, pids, &ctx, 0);
		cmd = cmd->next;
	}
	wait_all(cmd, pids, &ctx, pipes);
	return (r);
}
