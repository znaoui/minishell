/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:39:18 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/10 15:21:28 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parsing.h"
#include "libft.h"

int	handle_single_quotes(char **str, int start)
{
	int	quotes;

	quotes = 0;
	while ((*str)[start] != 0)
	{
		if ((*str)[start] == '\'')
		{
			*str = remove_substr(*str, start--, 1);
			if (++quotes == 2)
				return (start);
		}
		start++;
	}
	return (start);
}

int	handle_env_var(char **str, int start, int len)
{
	char	*key;
	char	*value;

	key = ft_substr(*str, start, len);
	value = get_env(&key[1]);
	if (value == NULL)
		*str = remove_substr(*str, start, len);
	else
	{
		*str = replace_str(*str, start, len, value);
		start += ft_strlen(value);
	}
	start--;
	free(key);
	return (start);
}

int	handle_dollar_sign(char **str, int start)
{
	int		i;
	char	*tmp;

	if ((*str)[start + 1] == '?')
	{
		tmp = ft_itoa(g_config.exit_code);
		*str = replace_str(*str, start, 2, tmp);
		free(tmp);
	}
	else if ((*str)[start + 1] != '"' && (*str)[start + 1] != '\''
			&& (*str)[start + 1] != ' ')
	{
		i = start + 1;
		while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
			i++;
		if (i > start + 1)
			start = handle_env_var(str, start, i - start);
	}
	return (start);
}

int	handle_double_quotes(char **str, int start, int expand)
{
	int		quotes;

	quotes = 0;
	while ((*str)[start] != 0)
	{
		if ((*str)[start] == '"')
		{
			*str = remove_substr(*str, start--, 1);
			if (++quotes == 2)
				return (start);
		}
		else if (BACKSLASH_ESCAPE && (*str)[start] == '\\')
		{
			if ((*str)[start + 1] == '$' || (*str)[start + 1] == '"'
				|| (*str)[start + 1] == '\\')
				*str = remove_substr(*str, start, 1);
		}
		else if (expand && (*str)[start] == '$')
			start = handle_dollar_sign(str, start);
		start++;
	}
	return (start);
}

char	*process_arg(char *arg, int heredoc)
{
	int	i;
	int	env_var;

	env_var = (*arg == '$' && !ft_strchr(arg, '\'') && !ft_strchr(arg, '"'));
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '"')
			i = handle_double_quotes(&arg, i, !heredoc);
		else if (arg[i] == '\'')
			i = handle_single_quotes(&arg, i);
		else if (!heredoc && arg[i] == '$')
			i = handle_dollar_sign(&arg, i);
		else if (BACKSLASH_ESCAPE && arg[i] == '\\')
			arg = remove_substr(arg, i, 1);
		if (i >= 0 && !arg[i])
			break ;
	}
	if (env_var && !*arg)
	{
		free(arg);
		return (NULL);
	}
	return (arg);
}
