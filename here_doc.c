/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:09 by iassil            #+#    #+#             */
/*   Updated: 2024/03/19 03:30:14 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <sys/wait.h>

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

void	ft_get_the_line(char **line, char **hold, int *pipefd)
{
	while (true)
	{
		ft_putstr("> ", 1);
		*line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(*hold, *line, ft_strlen(*hold)) == 0)
		{
			(free(*hold), free(*line));
			break ;
		}
		ft_putstr(*line, pipefd[1]);
		free(*line);
	}
}

int	ft_input_child(char *delimiter, t_env *env)
{
	int		pipefd[2];
	char	*line;
	char	*hold;
	int		status;
	pid_t	id;

	ft_syscall(pipe(pipefd), "pipe");
	id = fork();
	ft_syscall(id, "fork");
	if (id == 0)
	{
		ft_syscall(close(pipefd[0]), "close");
		line = NULL;
		hold = ft_strjoin(delimiter, "\n");
		ft_check_allocation(hold);
		ft_get_the_line(&line, &hold, pipefd);
		ft_syscall(close(pipefd[1]), "close");
		exit(SUCCESS);
	}
	close(pipefd[1]);
	waitpid(CHILD, &status, 0);
	env->status = WEXITSTATUS(status);
	return (pipefd[0]);
}
