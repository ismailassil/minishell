/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 03:10:20 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_open_infile_or_heredoc(t_cont *cont, t_fd *fd, t_env *env)
{
	t_fd_	f_d;

	f_d.i = -1;
	while (cont->infile && cont->infile[++f_d.i] != 0)
	{
		f_d.infile = open(cont->infile[f_d.i], O_RDONLY);
		if (f_d.infile == -1)
			return (ft_error("msh: "), perror(cont->infile[f_d.i]), \
				env->status = 1, 1);
		fd->infile = f_d.infile;
		fd->opened_fd[fd->len++] = fd->infile;
	}
	f_d.i = -1;
	while (cont->here_doc && cont->here_doc[++f_d.i] != 0)
	{
		f_d.here_doc = ft_here_doc(cont->here_doc[f_d.i], env);
		if (*cont->file_or_heredoc == 1)
		{
			fd->infile = f_d.here_doc;
			fd->opened_fd[fd->len++] = fd->infile;
		}
		else
			ft_syscall(close(f_d.here_doc), "close");
	}
	return (0);
}

int	ft_open_files(t_cont *cont, t_fd *fd, t_env *env)
{
	t_fd_	f_d;

	f_d.i = -1;
	while (cont->outfile && cont->outfile[++f_d.i] != 0)
	{
		if (cont->outfile_type[f_d.i] == 1)
			f_d.outfile = open(cont->outfile[f_d.i], O_CREAT | O_WRONLY, 0644);
		else if (cont->outfile_type[f_d.i] == 2)
			f_d.outfile = open(cont->outfile[f_d.i], \
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (f_d.outfile == -1)
			return (ft_error("msh: "), perror(cont->outfile[f_d.i]), \
				env->status = 1, 1);
		fd->outfile = f_d.outfile;
		fd->opened_fd[fd->len++] = fd->outfile;
	}
	if (ft_open_infile_or_heredoc(cont, fd, env) == 1)
		return (1);
	return (0);
}

void	ft_check_allocation(void *str)
{
	if (str == NULL)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
}

void	ft_syscall(int return_, char *str)
{
	if (return_ == -1)
		(perror(str), exit(FAIL));
}

void	ft_f(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_free_tmp(t_tmp_cont **tmp)
{
	int	i;

	i = 0;
	free((*tmp)->cmd);
	while ((*tmp)->arg[i] != NULL)
		(1) && (free((*tmp)->arg[i]), i++);
	free((*tmp)->arg);
	i = 0;
	while ((*tmp)->inf[i] != NULL)
		(1) && (free((*tmp)->inf[i]), i++);
	free((*tmp)->inf);
	i = 0;
	while ((*tmp)->outf[i] != NULL)
		(1) && (free((*tmp)->outf[i]), i++);
	free((*tmp)->outf);
	free((*tmp)->out_t);
	free(*tmp);
}
