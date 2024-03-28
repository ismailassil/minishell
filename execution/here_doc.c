/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:09 by iassil            #+#    #+#             */
/*   Updated: 2024/03/28 20:30:00 by iassil           ###   ########.fr       */
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
	char	*delimiter;

	line = NULL;
	delimiter = ft_trim_quotes(hold);
	rl_catch_signals = 1;
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(delimiter, line) == 0 || line == NULL)
		{
			(free(line), free(delimiter));
			break ;
		}
		free(line);
	}
}

int	ft_here_doc_parsing(t_token *lst, t_struct *strp)
{
	t_heredoc	info;

	while (lst != NULL)
	{
		if (lst->type == HEREDOC && lst->next && lst->next->type != DELIMITER)
			return (0);
		if (lst->type == HEREDOC && lst->next && lst->next->type == DELIMITER)
		{
			(1) && (info.del = lst->next->token, info.id = fork());
			ft_syscall(info.id, "msh: fork");
			if (info.id == 0)
			{
				ft_sig(signal(SIGINT, SIG_DFL), "msh: signal");
				ft_sig(signal(SIGQUIT, SIG_IGN), "msh: signal");
				ft_get_the_line_parsing(info.del);
				exit(SUCCESS);
			}
			ft_syscall(waitpid(CHILD, &info.status, 0), "msh: waitpid");
			if (WIFSIGNALED(info.status) && WTERMSIG(info.status) == SIGINT)
				return (strp->status = 1, 1);
		}
		lst = lst->next;
	}
	return (0);
}

static void	ft_get_the_line(char *hold, int *pipefd, t_struct *strp)
{
	char	*line;
	char	*delimiter;
	int		flag;

	(1) && (line = NULL, flag = 0);
	if (ft_strchr(hold, '\'') || ft_strchr(hold, '"'))
		flag = 1;
	delimiter = ft_trim_quotes(hold);
	rl_catch_signals = 1;
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(delimiter, line) == 0 || line == NULL)
		{
			(free(line), free(delimiter));
			break ;
		}
		if (ft_strchr(line, '$') && ft_check_brackets(line) == 1 && flag == 0)
			line = ft_strdup("msh: bad substitution");
		else if (ft_strchr(line, '$') && flag == 0)
			line = ft_handle_expand_for_here_doc(strp, line);
		line = ft_strjoin_(line, "\n");
		ft_check_allocation(line);
		(ft_putstr(line, pipefd[1]), free(line));
	}
}

int	ft_here_doc(char *delimiter, t_struct *strp)
{
	int			pipefd[2];
	t_heredoc	info;

	ft_syscall(pipe(pipefd), "msh: pipe");
	info.id = fork();
	ft_syscall(info.id, "msh: fork");
	if (info.id == 0)
	{
		ft_sig(signal(SIGINT, SIG_DFL), "msh: signal");
		ft_sig(signal(SIGQUIT, SIG_IGN), "msh: signal");
		ft_syscall(close(pipefd[0]), "msh: close");
		ft_get_the_line(delimiter, pipefd, strp);
		ft_syscall(close(pipefd[1]), "msh: close");
		exit(SUCCESS);
	}
	ft_syscall(close(pipefd[1]), "msh: close");
	ft_syscall(waitpid(CHILD, &info.status, 0), "msh: waitpid");
	strp->status = WEXITSTATUS(info.status);
	if (WIFSIGNALED(info.status) && WTERMSIG(info.status) == SIGINT)
		return (strp->status = 1, -1);
	return (pipefd[0]);
}
