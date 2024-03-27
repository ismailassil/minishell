/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:44:37 by iassil            #+#    #+#             */
/*   Updated: 2024/03/27 19:53:32 by aibn-che         ###   ########.fr       */
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

/*
*	this function help us to decide wether we are dealing with $ followed by quote or not
*/

int	quote_after_dollar_sign(char *str, int i)
{
	int	c;

	c = str[i++];
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_special_chars(t_expand *exp, char *arg, int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (arg[(*i) + 1] == '-')
	{
		(1) && (exp->new_str = ft_strjoin_(s, "himBH"), *i += 1);
		free(s);
	}
	else if (arg[(*i) + 1] == '?')
		ft_question_mark(exp, s, i, strp);
	else if (exp->quote == '\"' && arg[(*i) + 1] == '\"')
		ft_append_char(&exp->new_str, '$');
	else if ((arg[(*i) + 1] == '\'' || arg[(*i) + 1] == '\"') && quote_after_dollar_sign(arg, (*i) + 1))
		return ;
	else
		ft_append_char(&exp->new_str, '$');
}

int	ft_handle_irregulare_cases(t_expand *exp, char *arg, int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (ft_isdigit(arg[(*i) + 1]))
	{
		if (arg[(*i) + 1] == '0')
		{
			exp->new_str = ft_strjoin_(s, "minishell");
			free(s);
		}
		return ((*i += 2), 1);
	}
	else if (!ft_check_if_chars_digit(arg[(*i) + 1]))
	{
		ft_special_chars(exp, arg, i, strp);
		return ((*i += 1), 1);
	}
	return (0);
}
