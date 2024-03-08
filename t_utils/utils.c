/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:12:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 21:19:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_allocate_for_the_rest(t_tmp_cont *tmp, t_cont **new)
{
	int	i;

	i = 0;
	while (*(tmp->arg) != 0)
	{
		(*new)->arg[i] = ft_strdup(tmp->arg[i]);
		i++;
	}
	i = 0;
	while (*(tmp->infile) != 0)
	{
		(*new)->infile[i] = ft_strdup(tmp->infile[i]);
		i++;
	}
	i = 0;
	while (*(tmp->outfile) != 0)
	{
		(*new)->outfile[i] = ft_strdup(tmp->outfile[i]);
		i++;
	}
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
