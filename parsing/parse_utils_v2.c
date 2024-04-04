/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:44:37 by iassil            #+#    #+#             */
/*   Updated: 2024/04/04 18:08:51 by aibn-che         ###   ########.fr       */
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
*	this function help us to decide wether we are dealing
*	with $ followed by quote or not
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
	else if ((arg[(*i) + 1] == '\'' || arg[(*i) + 1] == '\"')
		&& quote_after_dollar_sign(arg, (*i) + 1)
		&& (exp->quote != '\'' && exp->quote != '\"'))
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

int	ft_expand_word_after_dollar(t_expand *exp, int *i,
	char *arg, t_struct *strp)
{
	char	*s;
	int		i_to_pass;

	i_to_pass = 0;
	s = NULL;
	if (exp->quote == '\'')
	{
		ft_append_char(&exp->new_str, arg[(*i)++]);
		return (1);
	}
	if (ft_between_bracket(arg, *i + 1) >= 2)
	{
		i_to_pass = ft_between_bracket(arg, *i + 1);
		(*i) += 1;
	}
	if (ft_handle_irregulare_cases(exp, arg, i, strp))
		return (1);
	exp->expa = ft_arg_is_exist(strp->env, arg + (*i + 1));
	s = exp->new_str;
	exp->new_str = ft_strjoin_(exp->new_str, exp->expa);
	(free(s), free(exp->expa));
	if (i_to_pass)
		return ((*i) = (i_to_pass), 1);
	return (0);
}
