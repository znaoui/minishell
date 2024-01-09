/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:08:39 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/02 00:34:13 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	char_bckw(char *str, char *start, char c)
{
	int	i;

	i = 0;
	while (str != start)
	{
		str--;
		if (*str != c)
			break ;
		i++;
	}
	return (i);
}

char	**reallocate_and_push(char **arr, char *str, int size)
{
	int		i;
	char	**new;

	new = (char **)malloc(sizeof(char *) * (size + 2));
	if (new)
	{
		i = -1;
		while (++i < size)
			new[i] = arr[i];
		new[i] = str;
		new[i + 1] = NULL;
	}
	if (arr)
		free(arr);
	return (new);
}

char	*replace_str(char *str, int index, int len, char *new)
{
	char	*ret;
	int		slen;
	int		new_len;
	int		s;
	char	*start;

	slen = ft_strlen(str);
	start = &str[index];
	s = 1;
	new_len = ft_strlen(new);
	ret = (char *)ft_calloc(sizeof(char), (slen - len + new_len) + 1);
	if (str != start && start > str)
		s = ft_strlcat(ret, str, start - str + 1);
	s = ft_strlcat(ret, new, s + new_len);
	if (start[len] != 0 && start >= str)
		s = ft_strlcat(ret, &start[len],
				s + (slen - (start - str) - len + 1));
	if (ret != str)
		free(str);
	return (ret);
}

char	*remove_substr(char *str, int index, int len)
{
	char	*s1;
	char	*s2;
	char	*ret;
	int		slen;

	slen = ft_strlen(str);
	s1 = NULL;
	s2 = NULL;
	if (index != 0)
		s1 = ft_substr(str, 0, index);
	if ((s1 && index != slen - 1) || !s1)
		s2 = ft_substr(str, index + len, slen - (index + len));
	free(str);
	if (s1 && s2)
	{
		ret = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
		return (ret);
	}
	else if (s1)
		return (s1);
	return (s2);
}

t_cmd	*new_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = CMD;
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->in_redir = NULL;
	cmd->out_redir = NULL;
	cmd->next = NULL;
	return (cmd);
}
