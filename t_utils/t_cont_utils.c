/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cont_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:25:31 by iassil            #+#    #+#             */
/*   Updated: 2024/04/24 10:48:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_t_cont_len(t_cont *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

static t_cont	*ft_last_node_cont(t_cont *top)
{
	while (top->next != NULL)
		top = top->next;
	return (top);
}

int	ft_push_container(t_tmp_cont *tmp, t_cont **head)
{
	t_cont	*newnode;
	t_cont	*last;

	newnode = ft_new_node_for_cont(tmp);
	if (!newnode)
		return (0);
	if (!head || !(*head))
		*head = newnode;
	else
	{
		last = ft_last_node_cont(*head);
		last->next = newnode;
	}
	return (1);
}

void	ft_free_the_rest(t_cont *c)
{
	free(c->outfile_is_var);
	free(c->outfile_type);
	free(c->file_or_heredoc);
	free(c->arg_is_var);
	free(c->arg_is_quote);
	free(c->infile_is_quote);
	free(c->outfile_is_quote);
	free(c->infile_is_var);
	free(c->here_doc_fd);
	free(c->infile_index);
	free(c->outfile_index);
	free(c->inf_is_amb);
	free(c->out_is_amb);
}

void	ft_free_containers(t_cont **head)
{
	t_cont	*c;
	int		i;

	while (*head)
	{
		(1) && (c = *head, *head = (*head)->next, i = 0);
		free(c->cmd);
		ft_f(c->arg);
		ft_f(c->infile);
		ft_f(c->inf_before);
		ft_f(c->here_doc);
		ft_f(c->outfile);
		ft_f(c->out_before);
		ft_free_the_rest(c);
		(free(c), c = NULL);
	}
	(free(*head), head = NULL);
}
