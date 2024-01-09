/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:24:03 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/15 18:05:43 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	has_str_starts_with(char **arr, char *str, int size);
int	array_size(char **arr);

char	**unset_new(char *prefix, int size)
{
	int		i;
	int		z;
	int		len;
	char	**new;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	len = ft_strlen(prefix);
	i = -1;
	z = 0;
	while (g_config.env[z])
	{
		if (ft_strncmp(g_config.env[z], prefix, len) != 0)
			new[++i] = g_config.env[z];
		else
			free(g_config.env[z]);
		z++;
	}
	new[++i] = NULL;
	return (new);
}

int	unset_env(char *key)
{
	char	*tmp;
	int		size;
	char	**new;

	size = array_size(g_config.env);
	tmp = ft_strjoin(key, "=");
	if (!has_str_starts_with(g_config.env, tmp, size))
	{
		free(tmp);
		return (0);
	}
	new = unset_new(tmp, size);
	free(tmp);
	free(g_config.env);
	g_config.env = new;
	return (1);
}

int	set_env(char *key, char *value)
{
	int		size;
	char	**new;
	int		i;
	char	*tmp;

	if (!key)
		return (0);
	tmp = ft_strjoin(key, "=");
	i = -1;
	unset_env(key);
	size = array_size(g_config.env);
	new = (char **)malloc(sizeof(char *) * (size + 2));
	while (++i < size)
		new[i] = g_config.env[i];
	if (!value)
		value = "";
	new[i] = ft_strjoin(tmp, value);
	new[i + 1] = NULL;
	free(tmp);
	free(g_config.env);
	g_config.env = new;
	return (1);
}

char	*get_env(char *key)
{
	char	**env;
	int		len;

	len = ft_strlen(key);
	env = g_config.env;
	while (*env)
	{
		if (!ft_strncmp(*env, key, len)
			&& (*env)[len - 1] && (*env)[len] == '=')
			break ;
		env++;
	}
	if (*env != NULL)
		return (&(*env)[++len]);
	return (NULL);
}
