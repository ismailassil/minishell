/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:09 by iassil            #+#    #+#             */
/*   Updated: 2024/04/23 19:19:38 by iassil           ###   ########.fr       */
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
	if (ft_check_del_and_quotes(hold))
	{
		delimiter = ft_remove_for_del(hold);
		free(hold);
	}
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
				ft_sig(signal(SIGQUIT, &ft_sig_quit), "msh: signal");
				ft_free_env(&strp->env);
				ft_get_the_line_parsing(info.del);
				exit(SUCCESS);
			}
			ft_syscall(waitpid(CHILD, &info.status, 0), "waitpid");
			if (WIFSIGNALED(info.status) && WTERMSIG(info.status) == SIGINT)
				return (printf("\n"), strp->status = 1, 1);
		}
		lst = lst->next;
	}
	return (0);
}

static void	ft_get_the_line(char *hold, int *pipefd, t_struct *strp)
{
	t_info_here_doc	f;

	(1) && (f.line = NULL, f.flag = 0);
	if (ft_strchr(hold, '\'') || ft_strchr(hold, '"'))
		f.flag = 1;
	if (ft_check_del_and_quotes(hold))
	{
		f.delimiter = ft_remove_for_del(hold);
		free(hold);
		hold = f.delimiter;
	}
	rl_catch_signals = 1;
	while (true)
	{
		f.line = readline("> ");
		if (ft_strcmp(hold, f.line) == 0 || f.line == NULL)
		{
			(free(f.line), free(hold));
			break ;
		}
		ft_check_dollar_sign_here_doc(&f.line, pipefd[1], strp, f.flag);
		f.push = ft_join_(f.line, "\n");
		ft_check_allocation(f.push);
		(ft_putstr(f.push, pipefd[1]), free(f.push), free(f.line));
	}
}

int	ft_here_doc(char *delimiter, t_struct *strp)
{
	int			pipefd[2];
	t_heredoc	info;

	ft_syscall(pipe(pipefd), "pipe");
	info.id = fork();
	ft_syscall(info.id, "fork");
	if (info.id == 0)
	{
		ft_sig(signal(SIGINT, SIG_DFL), "msh: signal");
		ft_sig(signal(SIGQUIT, &ft_sig_quit), "msh: signal");
		ft_syscall(close(pipefd[0]), "close");
		ft_get_the_line(delimiter, pipefd, strp);
		ft_syscall(close(pipefd[1]), "close");
		exit(SUCCESS);
	}
	ft_syscall(close(pipefd[1]), "close");
	ft_syscall(waitpid(CHILD, &info.status, 0), "waitpid");
	strp->status = WEXITSTATUS(info.status);
	if (WIFSIGNALED(info.status) && WTERMSIG(info.status) == SIGINT)
		return (printf("\n"), strp->status = 1, -1);
	return (pipefd[0]);
}
