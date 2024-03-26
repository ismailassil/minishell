/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/25 18:39:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This function close the opened file descriptors
*/
void	close_opened_files(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->fd.len)
		close(info->fd.opened_fd[i++]);
}

/*
*	The main function for executing the commands
*/
void	ft_execution(t_token **token, t_struct *strp)
{
	t_token			*head;
	t_cont			*container;
	t_info			info;
	unsigned int	nbr_cont;

	head = *token;
	nbr_cont = 0;
	info.fd.len = 0;
	ft_link_all_in_containers(*token, &container);
	ft_free_tokens(&head);
	nbr_cont = ft_t_cont_len(container);
	if (ft_open_here_doc(container, &info, strp) == -1)
	{
		close_opened_files(&info);
		ft_free_containers(&container);
		return ;
	}
	ft_execute_multiple_cmds(container, strp, &info, nbr_cont);
	close_opened_files(&info);
	ft_free_containers(&container);
}
