/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:28:25 by cdudzik           #+#    #+#             */
/*   Updated: 2022/10/26 18:39:25 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>

// parametre de terminal "ctlecho" pour supprimer l'affichage de ^C
void	register_caps(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
