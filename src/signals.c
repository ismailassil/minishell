/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/04/28 19:07:40 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_default_signals(void)
{
	ft_sig(signal(SIGINT, SIG_DFL), "msh: signal");
	ft_sig(signal(SIGQUIT, SIG_DFL), "msh: signal");
}

void	ft_signal_handler(void)
{
	rl_catch_signals = 0;
	ft_sig(signal(SIGINT, ctrl_c), "msh: signal");
	ft_sig(signal(SIGQUIT, ctrl_slash), "msh: signal");
}

int	ft_status(int mode, int status_)
{
	static int	status;

	if (mode && status)
		return (status = 0, 1);
	status = status_;
	return (0);
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
		return ;
	if (waitpid(0, 0, 0) == -1)
		ft_status(0, 1);
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
		ft_syscall(tcsetattr(STDIN_FILENO, TCSANOW, &g_original_attr), \
			"tcsetattr");
		rl_replace_line("", 1);
		rl_on_new_line();
		return ;
	}
	rl_redisplay();
}
