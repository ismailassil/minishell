/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 17:18:47 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_d;
	struct sigaction	ctrl__;

	ctrl_c.sa_handler = ctrl_c_handler;
	ctrl_d.sa_handler = ctrl_d_handler;
	ctrl__.sa_handler = ctrl___handler;
	if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
		(perror("Error"), exit(EXIT_FAILURE));
	if (sigaction(SIGTERM, &ctrl_d, NULL) == -1)
		(perror("Error"), exit(EXIT_FAILURE));
	if (sigaction(SIGQUIT, &ctrl__, NULL) == -1)
		(perror("Error"), exit(EXIT_FAILURE));
}

void	ctrl_c_handler(int sig)
{
	(void)sig;
}

void	ctrl_d_handler(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

void	ctrl___handler(int sig)
{
	(void)sig;
}
