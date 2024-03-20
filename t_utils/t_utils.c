/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:12:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 14:31:18 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_allocate_for_rest_v2(t_tmp_cont *tmp, t_cont **new)
{
	int	i;

	i = 0;
	while (tmp->here_doc && tmp->here_doc[i] != 0)
		i++;
	(*new)->here_doc = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->here_doc && tmp->here_doc[i] != 0)
		(1) && ((*new)->here_doc[i] = ft_strdup(tmp->here_doc[i]), i++);
	(*new)->here_doc[i] = 0;
	(*new)->file_or_heredoc = tmp->file_or_heredoc;
}

static void	ft_allocate_for_rest(t_tmp_cont *tmp, t_cont **new)
{
	int	i;
	int	j;

	i = 0;
	while (tmp->out_t && tmp->out_t[i] != 0)
		i++;
	(*new)->outfile_type = malloc((i + 1) * sizeof(char *));
	j = 0;
	while (j < i)
	{
		(*new)->outfile_type[j] = tmp->out_t[j];
		j++;
	}
	(1) && ((*new)->outfile_type[j] = 0, i = 0);
	while (tmp->outf && tmp->outf[i] != 0)
		i++;
	(*new)->outfile = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->outf && tmp->outf[i] != 0)
		(1) && ((*new)->outfile[i] = ft_strdup(tmp->outf[i]), i++);
	(*new)->outfile[i] = 0;
	ft_allocate_for_rest_v2(tmp, new);
}

static void	ft_allocate_(t_tmp_cont *tmp, t_cont **new)
{
	int	i;

	i = 0;
	while (tmp->arg && tmp->arg[i] != 0)
		i++;
	(*new)->arg = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->arg && tmp->arg[i] != 0)
		(1) && ((*new)->arg[i] = ft_strdup(tmp->arg[i]), i++);
	(1) && ((*new)->arg[i] = 0, i = 0);
	while (tmp->inf && tmp->inf[i] != 0)
		i++;
	(*new)->infile = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->inf && tmp->inf[i] != 0)
		(1) && ((*new)->infile[i] = ft_strdup(tmp->inf[i]), i++);
	(*new)->infile[i] = 0;
	ft_allocate_for_rest(tmp, new);
}

t_cont	*ft_new_node_for_cont(t_tmp_cont *tmp)
{
	t_cont	*new;

	new = malloc(sizeof(t_cont));
	if (!new)
		return (NULL);
	if (tmp->cmd == NULL)
		new->cmd = NULL;
	else
	{
		new->cmd = ft_strdup(tmp->cmd);
		if (!new->cmd)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	ft_allocate_(tmp, &new);
	new->next = NULL;
	return (new);
}
