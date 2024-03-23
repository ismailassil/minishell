/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/03/23 22:53:55 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern struct termios	g_original_attr;

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

/*
*	It specifies that the waitpid() function should not wait for a child process
*	to exit if there are no child processes that have already exited and are
*	waiting to be reaped.
*/
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

/*
*	TCSANOW: It indicates that the changes to terminal attributes
*	should take effect immediately.
*/
void	ctrl_slash(int sig)
{
	(void)sig;
	if (waitpid(ALLCHILDS, NULL, WNOHANG) == 0)
	{
		ft_syscall(tcsetattr(STDIN_FILENO, TCSANOW, &g_original_attr),\
			"tcsetattr");
		printf("Quit: 3\n");
		return ;
	}
	rl_redisplay();
}
