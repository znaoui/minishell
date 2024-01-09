/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:00:58 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 14:56:42 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define MINISHELL_PREFIX "-minishell"

typedef enum e_file_type
{
	T_FILE,
	T_DIRECTORY,
	T_ERROR
}	t_file_type;

typedef struct e_exec_context
{
	char	*path;
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2];
	int		prev_read;
	int		has_pipe;
	int		ret;
	int		is_child;
}	t_exec_context;

char			*find_executable(t_cmd	*cmd);
void			*is_directory_error(char *path);
void			*cmd_error(char *path);
int				perror_null(void);
int				ambigous_redir_err(void);
int				handle_stdin(t_redirection *r, int *fd);
int				handle_stdout(t_redirection *r, int *fd);
void			reset_signals(void);
int				free_mem(t_cmd *cmd, pid_t *pid, t_exec_context *ctx, int end);
t_exec_context	get_ctx(t_cmd *cmd, int prev_read);
pid_t			*get_pids(t_cmd *first);
int				handle_heredocs(t_cmd *cmd);
int				heredoc(t_redirection *redir, char *file);
void			dup_all(t_cmd *cmd, t_exec_context *ctx);
int				exec_builtin_nopipe(t_cmd *cmd, t_exec_context *ctx);

#endif
