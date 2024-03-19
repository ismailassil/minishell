/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:09 by iassil            #+#    #+#             */
/*   Updated: 2024/03/19 18:03:00 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_get_the_line_parsing(char **line, char **hold)
{
	while (true)
	{
		ft_putstr("heredoc> ", STDIN_FILENO);
		*line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(*hold, *line, ft_strlen(*hold)) == 0)
		{
			(free(*hold), free(*line));
			break ;
		}
		free(*line);
	}
}

void	ft_here_doc_parsing(t_token *head, t_env *env)
{
	t_heredoc	info;

	while (head != NULL)
	{
		if (head->type == HEREDOC)
		{
			info.del = head->next->token;
			info.id = fork();
			ft_syscall(info.id, "fork");
			if (info.id == 0)
			{
				info.line = NULL;
				ft_default_signals();
				info.hold = ft_strjoin(info.del, "\n");
				ft_check_allocation(info.hold);
				ft_get_the_line_parsing(&info.line, &info.hold);
				exit(SUCCESS);
			}
			ft_syscall(waitpid(CHILD, &info.status, 0), "waitpid");
			env->status = WEXITSTATUS(info.status);
		}
		head = head->next;
	}
}

static void	ft_get_the_line(char **line, char **hold, int *pipefd)
{
	while (true)
	{
		write(1, "heredoc> ", 10);
		*line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(*hold, *line, ft_strlen(*hold)) == 0)
		{
			free(*hold);
			free(*line);
			break ;
		}
		ft_putstr(*line, pipefd[1]);
		free(*line);
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
		ft_syscall(close(pipefd[0]), "pipe");
		info.line = NULL;
		info.hold = ft_strjoin(delimiter, "\n");
		ft_get_the_line(&info.line, &info.hold, pipefd);
		ft_syscall(close(pipefd[1]), "pipe");
		exit(SUCCESS);
	}
	ft_syscall(close(pipefd[1]), "close");
	ft_syscall(waitpid(CHILD, &info.status, 0), "waitpid");
	env->status = WEXITSTATUS(info.status);
	return (pipefd[0]);
}
