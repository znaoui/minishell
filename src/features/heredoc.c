/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:10:53 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/15 18:20:35 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"
#include <errno.h>
#include "parsing.h"
#include <signal.h>

int		handle_dollar_sign(char **str, int start);
int		perror_null(void);
void	register_heredoc_signals(void);
void	replace_redir(t_redirection *redir, char *file);

char	*expand_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i] == '$' || str[i] == '\\'))
			str = remove_substr(str, i, 1);
		else if (str[i] == '$')
			i = handle_dollar_sign(&str, i);
		i++;
	}
	ret = ft_strjoin(str, "\n");
	free(str);
	return (ret);
}

int	read_heredoc(t_redirection *redir, int fd)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			if (!g_config.exit_code)
				ft_putstr_fd(HEREDOC_EOF_ERROR, 2);
			return (0);
		}
		else if (!ft_strcmp(str, redir->str))
		{
			free(str);
			break ;
		}
		else
		{
			str = expand_str(str);
			write(fd, str, ft_strlen(str));
			free(str);
		}
	}
	return (1);
}

void	write_heredoc(t_redirection *redir, char *file)
{
	int	fd;

	unlink(file);
	fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		g_config.exit_code = errno;
		return ;
	}
	read_heredoc(redir, fd);
	close(fd);
}

int	handle_heredoc(t_redirection *redir, char *file)
{
	g_config.cmd_is_running = 1;
	g_config.exit_code = 0;
	register_heredoc_signals();
	write_heredoc(redir, file);
	free(file);
	return (g_config.exit_code);
}

int	heredoc(t_redirection *redir, char *file)
{
	pid_t	pid;
	int		exit_code;

	exit_code = -1;
	pid = fork();
	if (pid < 0)
		return (perror_null());
	else if (pid == 0)
		return (handle_heredoc(redir, file));
	else
	{
		waitpid(pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			g_config.exit_code = WEXITSTATUS(exit_code);
		else
			g_config.exit_code = 130;
		if (!exit_code)
			replace_redir(redir, file);
		else
			free(file);
		if (g_config.exit_code == 130)
			return (-2);
		return (-1);
	}
}
