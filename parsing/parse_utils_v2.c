/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:44:37 by iassil            #+#    #+#             */
/*   Updated: 2024/03/25 18:40:36 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_question_mark(t_expand *exp, char *s, int *i, t_struct *strp)
{
	char	*num;

	num = ft_itoa(strp->status);
	exp->new_str = ft_strjoin_(s, num);
	*i += 1;
	free(s);
	free(num);
}

void	ft_special_characters(t_expand *exp, int c, int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (c == '-')
	{
		(1) && (exp->new_str = ft_strjoin_(s, "himBH"), *i += 1);
		free(s);
	}
	else if (c == '?')
		ft_question_mark(exp, s, i, strp);
	else
		ft_append_char(&exp->new_str, '$');
}

int	ft_handle_irregulare_cases(t_expand *exp, int c, int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (ft_isdigit(c))
	{
		if (c == '0')
		{
			exp->new_str = ft_strjoin_(s, "minishell");
			free(s);
		}
		return ((*i += 2), 1);
	}
	else if (!ft_check_if_chars_digit(c))
	{
		ft_special_characters(exp, c, i, strp);
		return ((*i += 1), 1);
	}
	return (0);
}
