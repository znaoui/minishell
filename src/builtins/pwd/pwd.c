/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:14:34 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/08 16:34:55 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_pwd(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("%s\n", g_config.pwd_cache);
	return (0);
}
