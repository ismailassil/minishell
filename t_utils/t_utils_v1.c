/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:12:35 by iassil            #+#    #+#             */
/*   Updated: 2024/04/24 11:22:42 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_allocate_for_here_doc(t_tmp_cont *tmp, t_cont **new)
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
	(*new)->file_or_heredoc = malloc(sizeof(int));
	*(*new)->file_or_heredoc = *tmp->file_or_heredoc;
	(*new)->here_doc_fd = malloc(sizeof(int));
	*(*new)->here_doc_fd = 0;
}

static void	ft_allocate_for_infile(t_tmp_cont *tmp, t_cont **new, int *i)
{
	*i = 0;
	while (tmp->inf && tmp->inf[*i] != 0)
		(*i)++;
	(*new)->infile = malloc((*i + 1) * sizeof(char *));
	ft_check_allocation((*new)->infile);
	(*new)->inf_before = malloc((*i + 1) * sizeof(char *));
	ft_check_allocation((*new)->inf_before);
	(*new)->infile_is_var = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->infile_is_var);
	(*new)->infile_is_quote = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->infile_is_quote);
	*i = 0;
	while (tmp->inf && tmp->inf[*i] != 0)
	{
		(*new)->infile[*i] = ft_strdup(tmp->inf[*i]);
		ft_check_allocation((*new)->infile[*i]);
		(*new)->infile_is_var[*i] = tmp->inf_is_var[*i];
		(*new)->infile_is_quote[*i] = tmp->inf_is_quote[*i];
		(*i)++;
	}
	(*new)->infile[*i] = 0;
	(*new)->infile_is_var[*i] = 0;
	(*new)->infile_is_quote[*i] = 0;
}

static void	ft_allocate_for_outfile(t_tmp_cont *tmp, t_cont **new, int *i)
{
	int	j;

	*i = 0;
	while (tmp->out_t && tmp->out_t[*i] != 0)
		(*i)++;
	(*new)->outfile_type = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->outfile_type);
	j = 0;
	while (j < *i)
		(1) && ((*new)->outfile_type[j] = tmp->out_t[j], j++);
	(1) && ((*new)->outfile_type[j] = 0, *i = 0);
	while (tmp->outf && tmp->outf[*i] != 0)
		(*i)++;
	(*new)->outfile = malloc((*i + 1) * sizeof(char *));
	ft_check_allocation((*new)->outfile);
	(*new)->out_before = malloc((*i + 1) * sizeof(char *));
	ft_check_allocation((*new)->out_before);
	(*new)->outfile_is_var = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->outfile_is_var);
	(*new)->outfile_is_quote = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->outfile_is_quote);
	ft_fill_for_outfile(tmp, new, i);
}

static void	ft_allocate_(t_tmp_cont *tmp, t_cont **new, int *i)
{
	*i = 0;
	while (tmp->arg && tmp->arg[*i] != 0)
		(*i)++;
	(*new)->arg = malloc((*i + 1) * sizeof(char *));
	ft_check_allocation((*new)->arg);
	(*new)->arg_is_var = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->arg_is_var);
	(*new)->arg_is_quote = malloc((*i + 1) * sizeof(int));
	ft_check_allocation((*new)->arg_is_quote);
	*i = 0;
	while (tmp->arg && tmp->arg[*i] != 0)
	{
		(*new)->arg[*i] = ft_strdup(tmp->arg[*i]);
		ft_check_allocation((*new)->arg[*i]);
		(*new)->arg_is_var[*i] = tmp->arg_is_var[*i];
		(*new)->arg_is_quote[*i] = tmp->arg_is_quote[*i];
		(*i)++;
	}
	(*new)->arg[*i] = 0;
	(1) && ((*new)->arg_is_var[*i] = 0, (*new)->arg_is_quote[*i] = 0);
	*i = 0;
	ft_allocate_for_infile(tmp, new, i);
	ft_allocate_for_outfile(tmp, new, i);
	ft_allocate_for_here_doc(tmp, new);
}

t_cont	*ft_new_node_for_cont(t_tmp_cont *tmp)
{
	t_cont	*new;
	int		i;

	new = malloc(sizeof(t_cont));
	if (!new)
		return (NULL);
	if (tmp->cmd == NULL)
		new->cmd = NULL;
	else
	{
		new->cmd = ft_strdup(tmp->cmd);
		ft_check_allocation(new->cmd);
		new->cmd_is_var = tmp->cmd_is_var;
		new->cmd_is_quote = tmp->cmd_is_quote;
	}
	i = 0;
	ft_allocate_(tmp, &new, &i);
	new->next = NULL;
	return (new);
}
