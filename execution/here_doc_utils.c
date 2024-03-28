/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:48:48 by iassil            #+#    #+#             */
/*   Updated: 2024/03/28 23:10:08 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This file hold the functions that expand the variables passed to here_doc
*/
static char	*ft_arg_is_exist_(t_env *env, char *var)
{
	t_env	*head;
	char	*ptr;
	int		i;
	int		flag;

	(1) && (head = env, i = 0, flag = 0, ptr = NULL);
	while (head != NULL)
	{
		i = 0;
		while (var[i] == head->value[i] && var[i] != '=')
			i++;
		if (head->value[i] == '=' && !ft_check_if_chars_digit(var[i]))
		{
			flag = 1;
			break ;
		}
		head = head->next;
	}
	if (head)
		ptr = ft_allocate_for_var(flag, head->value, i);
	return (ptr);
}

static int	ft_surpass_chars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}

static void	ft_question_mark_here_doc(t_expand *exp, char *s, int *i, t_struct *strp)
{
	char	*num;

	num = ft_itoa(strp->status);
	exp->new_str = ft_strjoin_(s, num);
	*i += 1;
	free(s);
	free(num);
}

void	ft_special_chars_here_doc(t_expand *exp, char *arg, int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (arg[(*i) + 1] == '-')
	{
		(1) && (exp->new_str = ft_strjoin_(s, "himBH"), *i += 1);
		free(s);
	}
	else if (arg[(*i) + 1] == '?')
		ft_question_mark_here_doc(exp, s, i, strp);
	else if (exp->quote == '\"' && arg[(*i) + 1] == '\"')
		ft_append_char(&exp->new_str, '$');
	else
		ft_append_char(&exp->new_str, '$');
}


int	ft_handle_irregulare_cases_here_doc(t_expand *exp, char *arg, int *i, t_struct *strp)
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
		ft_special_chars_here_doc(exp, arg, i, strp);
		return ((*i += 1), 1);
	}
	return (0);
}

static int	ft_expand_word_after_dollar_here_doc(t_expand *exp, int *i, \
	char *arg, t_struct *strp)
{
	char	*s;
	int		i_to_pass;

	i_to_pass = 0;
	s = NULL;
	if (ft_between_bracket(arg, *i + 1) >= 2)
	{
		i_to_pass = ft_between_bracket(arg, *i + 1);
		(*i) += 1;
	}
	if (ft_handle_irregulare_cases_here_doc(exp, arg, i, strp))
		return (1);
	exp->expa = ft_arg_is_exist_(strp->env, arg + (*i + 1));
	s = exp->new_str;
	exp->new_str = ft_strjoin_(exp->new_str, exp->expa);
	free(s);
	if (i_to_pass)
		return ((*i) = (i_to_pass), 1);
	return (0);
}

/*
*	This function expands the variables for the here_doc
*/
char	*ft_handle_expand_for_here_doc(t_struct *strp, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0);
	while (arg[i] != '\0')
	{
		if (arg[i] && arg[i] != '$')
			ft_append_char(&exp.new_str, arg[i++]);
		else if (arg[i] && arg[i] == '$')
		{
			if (ft_expand_word_after_dollar_here_doc(&exp, &i, arg, strp))
				continue ;
			i += ft_surpass_chars(arg + (i + 1));
		}
		else if (arg[i])
			i++;
	}
	return (exp.new_str);
}
