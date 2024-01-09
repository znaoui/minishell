/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:46:38 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/16 19:52:39 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	save_restore_fds(int restore)
{
	static int	fds[3];

	if (restore)
	{
		open(ttyname(fds[0]), O_APPEND | O_RDWR);
		open(ttyname(fds[1]), O_APPEND | O_RDWR);
		open(ttyname(fds[2]), O_APPEND | O_RDWR);
	}
	else
	{
		fds[0] = dup(STDIN_FILENO);
		fds[1] = dup(STDOUT_FILENO);
		fds[2] = dup(STDERR_FILENO);
	}
}

void	replace_redir(t_redirection *redir, char *file)
{
	free(redir->str);
	redir->type = REDIR_STDIN;
	redir->str = file;
}

void	heredoc_sig_handler(int sig)
{
	int		fd;
	char	**arg;

	if (sig == SIGINT)
	{
		g_config.exit_code = 130;
		fd = open("/dev/null", O_RDWR);
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		close(fd);
		arg = malloc(sizeof(char *) * 3);
		arg[0] = ft_strdup("/bin/exit");
		arg[1] = ft_strdup("130");
		arg[2] = NULL;
		execve(arg[0], arg, NULL);
		exit(130);
	}
}

void	register_heredoc_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = heredoc_sig_handler;
	sig.sa_flags = SA_NODEFER;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
}
