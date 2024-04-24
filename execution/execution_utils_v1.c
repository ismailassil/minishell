/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_v1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/04/24 19:13:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This function open the here_doc if found and keeps
*	the file descriptor opened
*/
int	ft_open_here_doc(t_cont *cont, t_info *info, t_struct *strp)
{
	t_cont	*head;
	t_fd_	f_d;

	(1) && (head = cont, f_d.i = 0);
	while (head != NULL)
	{
		f_d.i = 0;
		while (head->here_doc && head->here_doc[f_d.i] != 0)
		{
			*head->here_doc_fd = ft_here_doc(head->here_doc[f_d.i], strp);
			if (*head->here_doc_fd == -1)
				return (-1);
			if (head->here_doc && head->here_doc[f_d.i + 1] != NULL)
				ft_syscall(close(*head->here_doc_fd), "close");
			else
				info->fd.opened_fd[info->fd.len++] = *head->here_doc_fd;
			f_d.i++;
		}
		head = head->next;
	}
	return (0);
}

int	ft_builtin_exist(t_cont *cont)
{
	char	*cmd;

	cmd = cont->cmd;
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
