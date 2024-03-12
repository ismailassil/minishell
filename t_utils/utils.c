/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musashi <musashi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:12:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/12 16:06:59 by musashi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_allocate_for_the_rest(t_tmp_cont *tmp, t_cont **new)
{
	int	i;

	i = 0;
	while (tmp->arg[i] != 0)
		i++;
	(*new)->arg = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->arg[i] != 0)
		(1) && ((*new)->arg[i] = ft_strdup(tmp->arg[i]), i++);
	(1) && ((*new)->arg[i] = 0, i = 0);
	while (tmp->infile[i] != 0)
		i++;
	(*new)->infile = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->infile[i] != 0)
		(1) && ((*new)->infile[i] = ft_strdup(tmp->infile[i]), i++);
	(1) && ((*new)->infile[i] = 0, i = 0);
	while (tmp->append[i] != 0)
		i++;
	(*new)->append = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->append[i] != 0)
		(1) && ((*new)->append[i] = ft_strdup(tmp->append[i]), i++);
	(1) && ((*new)->append[i] = 0, i = 0);
	while (tmp->outfile[i] != 0)
		i++;
	(*new)->outfile = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp->outfile[i] != 0)
		(1) && ((*new)->outfile[i] = ft_strdup(tmp->outfile[i]), i++);
	(*new)->outfile[i] = 0;
}

t_cont	*ft_new_node_for_cont(t_tmp_cont *tmp)
{
	t_cont	*new;

	new = malloc(sizeof(t_cont));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(tmp->cmd);
	if (!new->cmd)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	ft_allocate_for_the_rest(tmp, &new);
	new->next = NULL;
	return (new);
}
