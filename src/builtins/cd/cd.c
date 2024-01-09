/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:05:14 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/09 14:53:58 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft.h"

char	*get_env(char *key);
int		perror_errno(void);
char	*current_directory(void);
int		set_env(char *key, char *value);

char	*get_new_path(char *arg)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(g_config.pwd_cache, "/");
	str = ft_strjoin(tmp, arg);
	free(tmp);
	return (str);
}

void	assign_new_pwd(void)
{
	free(g_config.pwd_cache);
	g_config.pwd_cache = current_directory();
	set_env("PWD", g_config.pwd_cache);
}

char	*get_home(void)
{
	char	*home;

	home = get_env("HOME");
	if (home)
		home = ft_strdup(home);
	return (home);
}

char	*get_path_from_arg(char *arg)
{
	if (arg[0] != '/')
		return (get_new_path(arg));
	return (ft_strdup(arg));
}

int	main_cd(int argc, char **argv)
{
	char	*path;

	if (argc == 1)
		path = get_home();
	else if (argc == 2)
		path = get_path_from_arg(argv[1]);
	else
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (path != NULL)
	{
		if (chdir(path) < 0)
		{
			free(path);
			return (perror_errno());
		}
		free(path);
		assign_new_pwd();
	}
	return (0);
}
