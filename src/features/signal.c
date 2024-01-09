/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:58:50 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/15 17:15:50 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include "minishell.h"

void	handler(int sig)
{
	if (!g_config.cmd_is_running && sig == SIGINT)
	{
		g_config.exit_code = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

//remplace l'action de CTRL+C
void	register_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = handler;
	sig.sa_flags = SA_NODEFER;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
