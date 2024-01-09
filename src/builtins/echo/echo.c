/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:48:59 by zaktarus          #+#    #+#             */
/*   Updated: 2022/11/16 19:46:51 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_n(char	*s)
{
	return (s[0] && s[0] == '-' && s[1] && s[1] == 'n');
}

static void	print_echo(int argc, char **argv, int *new_line)
{
	int	i;

	i = 0;
	while (++i < argc && is_n(argv[i]))
		*new_line = 0;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i + 1 < argc)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int	main_echo(int argc, char **argv)
{
	int	new_line;

	new_line = 1;
	if (argv[1])
		print_echo(argc, argv, &new_line);
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
