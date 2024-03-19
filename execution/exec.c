/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/19 20:36:00 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2(t_fd *fd)
{
	if (dup2(fd->infile, STDIN_FILENO) == -1)
		(perror("dup2 (STDIN)"), exit(FAIL));
	if (fd->infile != 0)
		close(fd->infile);
	if (dup2(fd->outfile, STDOUT_FILENO) == -1)
		(perror("dup2 (STDOUT)"), exit(FAIL));
	if (fd->outfile != 1)
		close(fd->outfile);
}

void	ft_execution(t_token **token, t_env *env)
{
	t_token			*head;
	t_cont			*container;
	unsigned int	nbr_cont;

	head = *token;
	nbr_cont = 0;
	ft_link_all_in_containers(*token, &container);
	nbr_cont = ft_t_cont_len(container);
	ft_execute_multiple_cmds(container, env, nbr_cont);
	ft_free_containers(&container);
}
