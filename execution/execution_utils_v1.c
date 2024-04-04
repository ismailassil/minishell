/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_v1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/04/04 00:41:02 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_amb_rdt(char **str, int type)
{
	int		i;
	char	**ptr;

	i = 0;
	if (type == 2)
		return (0);
	if ((*str) && (*str)[0] == '\0')
		return (ft_error("msh: ambiguous redirect\n"), 1);
	while ((*str) && ft_strchr(" \t\n\v\f\r", (*str)[i]) && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\0')
		return (ft_error("msh: ambiguous redirect\n"), 1);
	while ((*str)[i] != '\0')
	{
		if (ft_strchr(" \t\n\v\f\r", (*str)[i])
			&& !ft_strchr(" \t\n\v\f\r", (*str)[i + 1]))
			return (ft_error("msh: ambiguous redirect\n"), 1);
		i++;
	}
	if (ft_iswhitespace(*str) == 1)
	{
		ptr = ft_split_v2((*str));
		free((*str));
		(*str) = ptr[0];
	}
	return (0);
}

/*
*	This function checks and open files for the infiles and here_doc
*/
static int	ft_open_infile_or_heredoc(t_cont *cont, t_info *info,
	t_struct *strp)
{
	t_fd_	fd;

	fd.i = -1;
	while (cont->infile && cont->infile[++fd.i] != 0)
	{
		if (ft_amb_rdt(&cont->infile[fd.i], \
			cont->infile_is_var[fd.i]) == 1)
			return (strp->status = 1, 1);
		fd.infile = open(cont->infile[fd.i], O_RDONLY);
		if (fd.infile == -1)
			return (ft_error("msh: "), perror(cont->infile[fd.i]), \
				strp->status = 1, 1);
		if (cont->infile && cont->infile[fd.i + 1] != 0)
			ft_syscall(close(fd.infile), "msh: close");
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
int	ft_open_files(t_cont *cont, t_info *info, t_struct *strp)
{
	t_fd_	fd;

	fd.i = -1;
	while (cont->outfile && cont->outfile[++fd.i] != 0)
	{
		if (ft_amb_rdt(&cont->outfile[fd.i], cont->outfile_is_var[fd.i]) == 1)
			return (strp->status = 1, 1);
		if (cont->outfile_type[fd.i] == 1)
			fd.outfile = open(cont->outfile[fd.i], CR | WO, 0644);
		else if (cont->outfile_type[fd.i] == 2)
			fd.outfile = open(cont->outfile[fd.i], CR | WO | AP, 0644);
		if (fd.outfile == -1)
			return (ft_error("msh: "), perror(cont->outfile[fd.i]), \
				strp->status = 1, 1);
		if (cont->outfile && cont->outfile[fd.i + 1] != 0)
			ft_syscall(close(fd.outfile), "msh: close");
		else
		{
			info->fd.outfile = fd.outfile;
			info->fd.opened_fd[info->fd.len++] = info->fd.outfile;
		}
	}
	if (ft_open_infile_or_heredoc(cont, info, strp) == 1)
		return (1);
	return (0);
}

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
				ft_syscall(close(*head->here_doc_fd), "msh: close");
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
