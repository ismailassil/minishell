/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:09 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 03:29:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (ft_strncmp(hold, line, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

int	ft_here_doc_parsing(t_token *head, t_env *env)
{
	t_heredoc	info;

	while (head != NULL)
	{
		if (head->type == HEREDOC && head->next && head->next->type != DELIMITER)
			return (0);
		if (head->type == HEREDOC && head->next && head->next->type == DELIMITER)
		{
			(1) && (info.del = head->next->token, info.id = fork());
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
		head = head->next;
	}
	return (0);
}

static void	ft_get_the_line(char *hold, int *pipefd)
{
	char *line;

	line = NULL;
	rl_catch_signals = 1;
	while (true)
	{
		line = readline("> ");
		if (ft_strncmp(hold, line, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
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
		ft_get_the_line(delimiter, pipefd);
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
