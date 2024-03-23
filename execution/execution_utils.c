/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/03/23 19:43:17 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This function checks and open files for the infiles and here_doc
*/
static int	ft_open_infile_or_heredoc(t_cont *cont, t_info *info, t_env *env)
{
	t_fd_	fd;

	fd.i = -1;
	while (cont->infile && cont->infile[++fd.i] != 0)
	{
		fd.infile = open(cont->infile[fd.i], O_RDONLY);
		if (fd.infile == -1)
			return (ft_error("msh: "), perror(cont->infile[fd.i]), \
				env->status = 1, 1);
		if (cont->infile && cont->infile[fd.i + 1] != 0)
			ft_syscall(close(fd.infile), "close");
		else
		{
			info->fd.infile = fd.infile;
			info->fd.opened_fd[info->fd.len++] = info->fd.infile;
		}
	}
	if (*cont->file_or_heredoc == 1)
		info->fd.infile = *cont->here_doc_fd;
	return (0);
}

/*
*	This function checks and open files for the outfiles
*/
int	ft_open_files(t_cont *cont, t_info *info, t_env *env)
{
	t_fd_	fd;

	fd.i = -1;
	while (cont->outfile && cont->outfile[++fd.i] != 0)
	{
		if (cont->outfile_type[fd.i] == 1)
			fd.outfile = open(cont->outfile[fd.i], O_CREAT | O_WRONLY, 0644);
		else if (cont->outfile_type[fd.i] == 2)
			fd.outfile = open(cont->outfile[fd.i], \
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd.outfile == -1)
			return (ft_error("msh: "), perror(cont->outfile[fd.i]), \
				env->status = 1, 1);
		if (cont->outfile && cont->outfile[fd.i + 1] != 0)
			ft_syscall(close(fd.outfile), "close");
		else
		{
			info->fd.outfile = fd.outfile;
			info->fd.opened_fd[info->fd.len++] = info->fd.outfile;
		}
	}
	if (ft_open_infile_or_heredoc(cont, info, env) == 1)
		return (1);
	return (0);
}

/*
*	This function open the here_doc if found and keeps
*	the file descriptor opened
*/
void	ft_open_here_doc(t_cont *cont, t_info *info, t_env *env)
{
	t_cont	*head;
	t_fd_	f_d;

	(1) && (head = cont, f_d.i = 0);
	while (head != NULL)
	{
		f_d.i = 0;
		while (head->here_doc && head->here_doc[f_d.i] != 0)
		{
			*head->here_doc_fd = ft_here_doc(head->here_doc[f_d.i], env);
			if (head->here_doc && head->here_doc[f_d.i + 1] != NULL)
				ft_syscall(close(*head->here_doc_fd), "close");
			else
				info->fd.opened_fd[info->fd.len++] = *head->here_doc_fd;
			f_d.i++;
		}
		head = head->next;
	}
}

int	ft_builtin_exist(t_cont *cont)
{
	char	*cmd;

	cmd = cont->cmd;
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

int	ft_check_cont_and_cmd(t_cont *cont, \
	t_env *env, t_info *info, int nr_cont)
{
	if (cont == NULL)
		return (1);
	if (nr_cont == 1 && cont->cmd == NULL)
	{
		ft_open_files(cont, info, env);
		return (1);
	}
	if (nr_cont == 1 && ft_builtin_exist(cont) == 1)
	{
		ft_open_files(cont, info, env);
		ft_check_commands(cont, env, info, 1);
		return (1);
	}
	return (0);
}
