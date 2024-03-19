/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/03/19 20:35:48 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_default_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(FAIL);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(FAIL);
}

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
	// ft_disable_attr();
	// rl_catch_signals = 0;
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		(perror("Error"), exit(EXIT_FAILURE));
	if (signal(SIGQUIT, ctrl_slash) == SIG_ERR)
		(perror("Error"), exit(EXIT_FAILURE));
}

void	ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd(YELLOW_"\nminishell$ "RESET, STDOUT_FILENO);
}

void	ctrl_slash(int sig)
{
	(void)sig;
}
