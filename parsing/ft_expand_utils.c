/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:47:12 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/25 21:58:42 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_to_vars(t_struct *strp)
{
	if (strp->is_filename)
	{
		strp->current->vars[strp->current->i] = ft_strdup("1");
		ft_check_allocation(strp->current->vars[strp->current->i++]);
	}
}

void	ft_add_val_to_vars(t_struct *strp, t_env *head, int i)
{
	strp->current->vars[strp->current->i] = ft_substr(head->value, \
		i + 1, ft_strlen(head->value) - i);
	ft_check_allocation(strp->current->vars[strp->current->i++]);
}

void	ft_save_var_name_and_value(t_expand_arg *f, t_file **new, t_struct *strp)
{
	(*new) = malloc(sizeof(t_file));
	ft_check_allocation((*new));
	(*new)->i = 0;
	f->i = 0;
	f->is_dollar = 0;
	while (f->head->token[f->i])
	{
		if (f->head->token[f->i++] == '$')
			f->is_dollar++;
	}
	(*new)->vars = malloc((f->is_dollar + 1) * sizeof(char *));
	ft_check_allocation((*new)->vars);
	(*new)->before = ft_strdup(f->head->token);
	ft_check_allocation((*new)->before);
	(*new)->after = NULL;
	(*new)->next = NULL;
	(1) && ((*new)->status = 0, (*new)->i = 0);
	strp->current = (*new);
	ft_add_back(&strp->head, (*new));
	strp->is_filename = 1;
}

int	ft_surpass_cchars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}
