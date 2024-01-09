/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:23:18 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/15 17:50:06 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_valid_int(char *str)
{
	char	*tmp;
	int		i;

	tmp = str;
	if (*tmp == '-' || *tmp == '+')
		tmp++;
	while (*tmp && ft_isdigit(*(tmp++)))
		;
	if (*tmp != 0)
		return (0);
	i = ft_atoi(str);
	tmp = ft_itoa(i);
	if (tmp != NULL)
	{
		if ((*str == '+' && i >= 0) || (i == 0 && *str == '-'))
			str++;
		while (i != 0 && *str == '0')
			str++;
		i = ft_strncmp(tmp, str, ft_strlen(tmp)) == 0;
		free(tmp);
		return (i);
	}
	return (0);
}

int	main_exit(int argc, char **argv)
{
	int	code;

	code = g_config.exit_code;
	if (argc > 1 && !is_valid_int(argv[1]))
	{
		ft_putstr_fd("-minishell: exit: numeric argument required\n", 2);
		code = 2;
	}
	else if (argc > 2)
	{
		ft_putstr_fd("-minishell: exit: too many arguments\n", 2);
		code = 1;
		g_config.exit_code = -1;
	}
	else if (argc == 2)
	{
		code = ft_atoi(argv[1]);
		if (code > 0 || (code < 0 && code < -256))
			code %= 256;
		else if (code < 0)
			code = 256 + code;
	}
	return (code);
}
