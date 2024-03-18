/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 15:18:44 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_files(t_cont *cont, t_fd *fd)
{
	int	i;
	int	fd_infile[OPEN_MAX];
	int	fd_outfile[OPEN_MAX];

	(1) && (i = -1, fd->outfile = 1);
	while (cont->outfile && cont->outfile[++i] != 0)
	{
		if (cont->outfile_type[i] == 1)
			fd_outfile[i] = open(cont->outfile[i], O_CREAT | O_WRONLY, 0644);
		else if (cont->outfile_type[i] == 2)
			fd_outfile[i] = open(cont->outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		fd->outfile = fd_outfile[i];
		if (fd_outfile[i] == -1)
			return (write(2, "msh: ", 5), perror(cont->outfile[i]), 1);
	}
	(1) && (i = -1, fd->infile = 0);
	while (cont->infile && cont->infile[++i] != 0)
	{
		fd_infile[i] = open(cont->infile[i], O_RDONLY);
		fd->infile = fd_infile[i];
		if (fd_infile[i] == -1)
			return (write(2, "msh: ", 5), perror(cont->infile[i]), 1);
	}
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
