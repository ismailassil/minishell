/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:21:11 by iassil            #+#    #+#             */
/*   Updated: 2024/04/04 03:01:59 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	i = 0;
	while ((*tmp)->inf[i] != NULL)
		(1) && (free((*tmp)->inf[i]), i++);
	i = 0;
	while ((*tmp)->outf[i] != NULL)
		(1) && (free((*tmp)->outf[i]), i++);
	i = 0;
	while ((*tmp)->here_doc[i] != NULL)
		(1) && (free((*tmp)->here_doc[i]), i++);
	(free((*tmp)->inf), free((*tmp)->outf), free((*tmp)->out_t));
	(free((*tmp)->arg), free((*tmp)->here_doc));
	(free((*tmp)->out_is_var), free((*tmp)->inf_is_var));
	free((*tmp)->arg_is_var);
	(free((*tmp)->file_or_heredoc), free(*tmp));
}
