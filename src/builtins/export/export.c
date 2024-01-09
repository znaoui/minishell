/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:13:18 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/15 18:03:54 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*replace_double_quotes(char *str);
int		set_env(char *key, char *value);

int	env_declare(void)
{
	int		i;
	char	*key;
	char	*tmp;
	char	*str;

	i = -1;
	while (g_config.env[++i])
	{
		tmp = ft_strchr(g_config.env[i], '=');
		key = ft_substr(g_config.env[i], 0, tmp - g_config.env[i]);
		str = replace_double_quotes(++tmp);
		printf("declare -x %s=\"%s\"\n", key, str);
		free(key);
		free(str);
	}
	return (0);
}

int	is_valid_key(char *k)
{
	if (!ft_isalpha(*k) && *k != '_')
		return (0);
	while (*k)
	{
		if (!ft_isalnum(*k) && *k != '_')
			return (0);
		k++;
	}
	return (1);
}

void	identifier_error(char *str, int *code)
{
	ft_putstr_fd("-minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*code = 1;
}

void	set_env_var(char *key, char *sep)
{
	char	*val;
	char	*tmp;

	val = sep + 1;
	if (*sep == '+')
	{
		tmp = get_env(key);
		if (key != NULL)
			val = ft_strjoin(tmp, sep + 2);
	}
	set_env(key, val);
	if (val != sep + 1)
		free(val);
}

int	main_export(int argc, char **argv)
{
	char	*sep;
	int		i;
	int		code;
	char	*key;

	code = 0;
	i = 0;
	if (argc == 1)
		return (env_declare());
	while (argv[++i])
	{
		sep = ft_strchr(argv[i], '=');
		if (!sep)
			continue ;
		if (argv[i] != sep && *(sep - 1) == '+')
			sep--;
		key = ft_substr(argv[i], 0, sep - argv[i]);
		if (!is_valid_key(key))
			identifier_error(argv[i], &code);
		else
			set_env_var(key, sep);
		free(key);
	}
	return (code);
}
