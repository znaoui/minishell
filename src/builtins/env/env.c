/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:45:45 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/08 18:10:58 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_env(int argc, char **argv)
{
	int		i;

	(void)argc;
	(void)argv;
	i = -1;
	while (g_config.env[++i])
		printf("%s\n", g_config.env[i]);
	return (0);
}
