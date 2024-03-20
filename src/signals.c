/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 14:06:25 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_default_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(FAIL);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(FAIL);
}

void	ft_signal_handler(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		(perror("Error"), exit(EXIT_FAILURE));
	if (signal(SIGQUIT, ctrl_slash) == SIG_ERR)
		(perror("Error"), exit(EXIT_FAILURE));
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (waitpid(ALLCHILDS, NULL, WNOHANG) == 0)
	{
		printf("\n");
		return ;
	}
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash(int sig)
{
	(void)sig;
}
