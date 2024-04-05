/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/04/05 02:49:25 by iassil           ###   ########.fr       */
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

static bool	ft_check_path_in_env(t_struct *strp, t_cont *cont)
{
	t_env	*head;
	char	*tobedisplayed;
	int		i;

	(1) && (i = 0, head = strp->env);
	while (head)
	{
		if (ft_strncmp(head->value, "PATH=", 5) == 0)
		{
			if (ft_strlen(head->value) > 5)
				return (false);
		}
		head = head->next;
	}
	if (cont->cmd && cont->cmd_is_arg == 1 && cont->cmd_is_quote != 1 && (cont->cmd)[0] == '\0')
	{
		while (ft_evar(cont->arg_is_var[i], cont->arg_is_quote[i], cont->arg[i]))
			i++;
		if (cont->arg[i] == 0)
			return (true);
		else
			tobedisplayed = cont->arg[i];
	}
	else
		tobedisplayed = cont->cmd;
	(ft_error("msh: "), ft_error(tobedisplayed));
	ft_error(": No such file or directory\n");
	strp->status = 127;
	return (true);
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
	if (ft_check_path_in_env(strp, container))
	{
		ft_free_containers(&container);
		return ;
	}
	ft_execute_multiple_cmds(container, strp, &info, nbr_cont);
	close_opened_files(&info);
	ft_free_containers(&container);
}
