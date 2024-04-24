/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:22:51 by iassil            #+#    #+#             */
/*   Updated: 2024/04/24 13:36:26 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_for_outfile(t_tmp_cont *tmp, t_cont **_new, int *i)
{
	*i = 0;
	while (tmp->outf && tmp->outf[*i] != 0)
	{
		(*_new)->outfile[*i] = ft_strdup(tmp->outf[*i]);
		ft_check_allocation((*_new)->outfile[*i]);
		(*_new)->outfile_is_var[*i] = tmp->out_is_var[*i];
		(*_new)->outfile_is_quote[*i] = tmp->out_is_quote[*i];
		(*i)++;
	}
	(1) && ((*_new)->outfile[*i] = 0, (*_new)->outfile_is_var[*i] = 0);
	(*_new)->outfile_is_quote[*i] = 0;
}

void	ft_free_t_file(t_file **filename_node)
{
	t_file	*head;
	t_file	*tobefreed;

	head = 	*filename_node;
	while (head != NULL)
	{
		tobefreed = head;
		head = head->next;
		ft_f(tobefreed->vars);
		free(tobefreed->before);
		free(tobefreed->after);
		free(tobefreed);
		tobefreed = NULL;
	}
}
