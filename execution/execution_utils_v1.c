/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_v1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/04/20 16:08:36 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_amb_rdt(char **s, int isvar, int isquote)
{
	t_amb_rdt	r;

	r.i = 0;
	if (isvar == 2)
		return (0);
	if (isquote != 1 && (*s) && (*s)[0] == '\0')
		return (ft_error("msh: ambiguous redirect\n"), 1);
	while ((*s) && ft_strchr(" \t\n\v\f\r", (*s)[r.i]) && (*s)[r.i] != '\0')
		r.i++;
	if (isquote != 1 && (*s)[r.i] == '\0')
		return (ft_error("msh: ambiguous redirect\n"), 1);
	while ((*s)[r.i] != '\0')
	{
		if (isquote != 1 && ft_strchr(" \t\n\v\f\r", (*s)[r.i])
			&& !ft_strchr(" \t\n\v\f\r", (*s)[r.i + 1]))
			return (ft_error("msh: ambiguous redirect\n"), 1);
		r.i++;
	}
	if (isvar == 1 && isquote != 1 && ft_iswhitespace(*s) == 1)
	{
		r.ptr = ft_split_v2((*s));
		free((*s));
		(*s) = r.ptr[0];
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
		if (ft_amb_rdt(&cont->infile[fd.i], cont->infile_is_var[fd.i], \
			cont->infile_is_quote[fd.i]) == 1)
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
int	ft_open_files(t_cont *c, t_info *info, t_struct *s)
{
	t_fd_	fd;

	fd.i = -1;
	while (c->outfile && c->outfile[++fd.i] != 0)
	{
		if (ft_amb_rdt(&c->outfile[fd.i], c->outfile_is_var[fd.i], \
			c->outfile_is_quote[fd.i]) == 1 || c->is_bad_sub == BAD_SUB)
			return (s->status = 1, 1);
		if (c->outfile_type[fd.i] == 1)
			fd.outfile = open(c->outfile[fd.i], CR | WO, 0644);
		else if (c->outfile_type[fd.i] == 2)
			fd.outfile = open(c->outfile[fd.i], CR | WO | AP, 0644);
		if (fd.outfile == -1)
			return (ft_throw_error(c->outfile[fd.i]), s->status = 1, 1);
		if (c->outfile && c->outfile[fd.i + 1] != 0)
			ft_syscall(close(fd.outfile), "msh: close");
		else
		{
			info->fd.outfile = fd.outfile;
			info->fd.opened_fd[info->fd.len++] = info->fd.outfile;
		}
	}
	if (ft_open_infile_or_heredoc(c, info, s) == 1)
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
			if (strp->is_bad_sub == BAD_SUB)
				(1) && (head->is_bad_sub = BAD_SUB, strp->is_bad_sub = 0);
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
