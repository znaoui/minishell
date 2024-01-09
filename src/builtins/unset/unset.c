/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:02:20 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/09 21:13:05 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		unset_env(char *key);
int		is_valid_key(char *k);

void	key_error(char *str, int *code)
{
	ft_putstr_fd("-minishell: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*code = 1;
}

int	main_unset(int argc, char **argv)
{
	int	i;
	int	code;

	code = 0;
	i = 0;
	if (argc == 1)
		return (0);
	while (argv[++i])
	{
		if (!is_valid_key(argv[i]))
			key_error(argv[i], &code);
		else
			unset_env(argv[i]);
	}
	return (code);
}
