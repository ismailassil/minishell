/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:44:37 by iassil            #+#    #+#             */
/*   Updated: 2024/03/23 17:45:12 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_question_mark(t_expand *exp, char *s, int *i, t_env *env)
{
	char	*num;

	num = ft_itoa(env->status);
	exp->new_str = ft_strjoin_(s, num);
	*i += 1;
	free(s);
	free(num);
}

int	ft_handle_irregulare_cases(t_expand *exp, int c, int *i, t_env *env)
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
		if (c == '-')
		{
			(1) && (exp->new_str = ft_strjoin_(s, "himBH"), *i += 1);
			free(s);
		}
		else if (c == '?')
			ft_question_mark(exp, s, i, env);
		else
			ft_append_char(&exp->new_str, '$');
		return ((*i += 1), 1);
	}
	return (0);
}
