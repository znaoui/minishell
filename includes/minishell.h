/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:17:50 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 16:56:43 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>

# define DEBUG 0
# define RUNNING_TESTS 0
# define BACKSLASH_ESCAPE 0
# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2
# define HEREDOC_PREFIX "/tmp/heredoc_minishell_"

// CMD END OF LINE / NO REDIRECTION
// PIPE |
typedef enum e_cmd_type
{
	CMD,
	PIPE,
	UNKNOWN_CMD_TYPE
}	t_cmd_type;

//REDIR_STDOUT >
//REDIR_STDOUT_APPEND >>
//REDIR_STDIN <
//REDIR_HEREDOC <<
typedef enum e_redir_type
{
	REDIR_STDOUT,
	REDIR_STDOUT_APPEND,
	REDIR_STDIN,
	REDIR_HEREDOC,
	REDIR_UNKNOWN
}	t_redir_type;

typedef struct e_redirection
{
	t_redir_type			type;
	char					*str;
	struct e_redirection	*next;
}	t_redirection;

typedef struct s_cmd
{
	t_cmd_type		type;
	int				argc;
	char			**argv;
	t_redirection	*in_redir;
	t_redirection	*out_redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell_config
{
	char			**env;
	int				exit_code;
	int				cmd_is_running;
	char			*pwd_cache;
}	t_minishell_config;

extern t_minishell_config	g_config;

t_cmd	*parse_rl(char *str);
void	register_signals(void);
void	register_caps(void);
int		exec_cmd(t_cmd	*cmd);
char	*get_env(char *key);

#endif
