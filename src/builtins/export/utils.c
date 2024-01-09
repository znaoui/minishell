/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:41:56 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/09 20:49:34 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*replace_str(char *str, int index, int len, char *new);

char	*replace_double_quotes(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_strdup(str);
	while (ret[i])
	{
		if (ret[i] == '"')
		{
			ret = replace_str(ret, i, 1, "\\\"");
			i++;
		}
		if (ret[i])
			i++;
	}
	return (ret);
}
