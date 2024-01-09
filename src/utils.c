/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:07:50 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/08 17:24:38 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

char	*current_directory(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) != NULL)
		return (ft_strdup(cwd));
	return (NULL);
}

int	has_str_starts_with(char **arr, char *str, int size)
{
	int	i;

	i = -1;
	while (++i < size && arr[i])
	{
		if (!ft_strncmp(arr[i], str, ft_strlen(str)))
			return (1);
	}
	return (0);
}

int	array_size(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}
