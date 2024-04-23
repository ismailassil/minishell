/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:12:31 by iassil            #+#    #+#             */
/*   Updated: 2024/04/23 20:35:11 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_push_matching(t_token **head, t_token *previous)
{
	t_push_matching	p;

	p.i = 0;
	p.newlist = NULL;
	p.dirs = NULL;
	p.dirs = ft_wildcards(&(*head)->token);
	if (p.dirs && p.dirs[p.i])
	{
		while (p.dirs[p.i])
			ft_push_token(p.dirs[p.i++], &p.newlist);
		ft_f(p.dirs);
		ft_token_list(*head, &p.newlist);
		ft_push_middle(previous, head, &p.newlist);
	}
	else
	{
		if (!p.dirs)
			ft_f(p.dirs);
		if ((ft_strchr((*head)->token, '"') || ft_strchr((*head)->token, '\''))
			&& (*head)->is_var != 1)
		{
			p.tmp = ft_trim_quotes((*head)->token);
			free((*head)->token);
			(*head)->token = p.tmp;
		}
	}
}

void	ft_match_wildcards(t_token **token)
{
	t_wildcards	w;

	w.head = *token;
	w.previous = NULL;
	while (w.head)
	{
		if (w.head->type == CMD && ft_strncmp(w.head->token, "export", 5) == 0)
			w.is_export = 1;
		else if (w.head->type == CMD)
			w.is_export = 0;
		if (w.is_export == 0 && ft_strchr(w.head->token, '*')
			&& w.head->type != FILENAME && w.head->type != DELIMITER)
		{
			ft_push_matching(&w.head, w.previous);
			if (w.previous == NULL)
				*token = w.head;
		}
		w.previous = w.head;
		if (w.head)
			w.head = w.head->next;
	}
}

void	ft_rm_quotes(char **input)
{
	t_wildcards	w;

	if (ft_strchr(*input, '"') || ft_strchr(*input, '\''))
	{
		w.tmp = ft_trim_quotes(*input);
		free(*input);
		*input = w.tmp;
	}
}
