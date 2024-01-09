/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:50:19 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/08 15:52:05 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include <stdio.h>
#include "minishell.h"
#include <errno.h>

void	*is_directory_error(char *path)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" : Is a directory\n", 2);
	g_config.exit_code = 126;
	return (0);
}

void	*cmd_error(char *path)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_config.exit_code = 127;
	return (0);
}

int	ambigous_redir_err(void)
{
	ft_putstr_fd("-minishell: ambiguous redirect\n", 2);
	g_config.exit_code = 1;
	return (0);
}

int	perror_null(void)
{
	g_config.exit_code = errno;
	perror(MINISHELL_PREFIX);
	return (0);
}

int	perror_errno(void)
{
	perror(MINISHELL_PREFIX);
	return (errno);
}
