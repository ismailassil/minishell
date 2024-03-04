/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/03/04 19:57:11 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_disable_attr(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		(perror("Error"), exit(EXIT_FAILURE));
	term.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		(perror("Error"), exit(EXIT_FAILURE));
}

void	ft_signal_handler(void)
{
	struct sigaction	sig1;
	struct sigaction	sig2;

	ft_disable_attr();
	sig1.sa_handler = ctrl_c;
	sig2.sa_handler = ctrl_slash;
	if (sigaction(SIGINT, &sig1, NULL) == -1
		|| sigaction(SIGQUIT, &sig2, NULL) == -1)
		(perror("Error"), exit(EXIT_FAILURE));
}

void	ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd(YELLOW_"\nminishell$ "RESET, STDOUT_FILENO);
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		(perror("Error"), exit(EXIT_FAILURE));
}

void	ctrl_slash(int sig)
{
	(void)sig;
	if (signal(SIGQUIT, ctrl_slash) == SIG_ERR)
		(perror("Error"), exit(EXIT_FAILURE));
}
