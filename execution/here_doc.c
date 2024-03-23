/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:09 by iassil            #+#    #+#             */
/*   Updated: 2024/03/23 23:11:31 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This file holds the functions that open the here_doc both for
*	parsing and execution
*/
void	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

static void	ft_get_the_line_parsing(char *hold)
{
	char	*line;

	line = NULL;
	rl_catch_signals = 1;
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(hold, line) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	slash_sig(int sig)
{
	(void)sig;
}

void	ft_default_signals_her_doc(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(FAIL);
	if (signal(SIGINT, slash_sig) == SIG_ERR)
		exit(FAIL);
}

int	ft_here_doc_parsing(t_token *lst, t_env *env)
{
	t_heredoc	info;

	while (lst != NULL)
	{
		if (lst->type == HEREDOC && lst->next && lst->next->type != DELIMITER)
			return (0);
		if (lst->type == HEREDOC && lst->next && lst->next->type == DELIMITER)
		{
			(1) && (info.del = lst->next->token, info.id = fork());
			ft_syscall(info.id, "fork");
			if (info.id == 0)
			{
				if (signal(SIGINT, SIG_DFL) == SIG_ERR)
					exit(FAIL);
				ft_get_the_line_parsing(info.del);
				exit(SUCCESS);
			}
			ft_syscall(waitpid(CHILD, &info.status, 0), "waitpid");
			env->status = WEXITSTATUS(info.status);
			if (WIFSIGNALED(info.status) && WTERMSIG(info.status) == SIGINT)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static void	ft_get_the_line(char *hold, int *pipefd, t_env *env)
{
	char	*line;

	line = NULL;
	rl_catch_signals = 1;
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(hold, line) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$'))
			line = ft_handle_expand_for_here_doc(env, line);
		line = ft_strjoin_(line, "\n");
		if (!line)
			(ft_error("Error: Allocation failed\n"), exit(FAIL));
		ft_putstr(line, pipefd[1]);
		free(line);
	}
}

int	ft_here_doc(char *delimiter, t_env *env)
{
	int			pipefd[2];
	t_heredoc	info;

	ft_syscall(pipe(pipefd), "pipe");
	info.id = fork();
	ft_syscall(info.id, "fork");
	if (info.id == 0)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			exit(FAIL);
		ft_syscall(close(pipefd[0]), "pipe");
		ft_get_the_line(delimiter, pipefd, env);
		ft_syscall(close(pipefd[1]), "pipe");
		exit(SUCCESS);
	}
	ft_syscall(close(pipefd[1]), "close");
	ft_syscall(waitpid(CHILD, &info.status, 0), "waitpid");
	env->status = WEXITSTATUS(info.status);
	if (WIFSIGNALED(info.status) && WTERMSIG(info.status) == SIGINT)
		exit(FAIL);
	return (pipefd[0]);
}
