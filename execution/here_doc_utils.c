/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:48:48 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 16:39:04 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_trim_word(char *arg)
// {
// 	char	*str;
// 	int		count;
// 	int		i;

// 	(1) && (i = 0, count = 0);
// 	while (arg && arg[i] != '\0' && ft_strchr(" \t\n\v\f\r", arg[i]))
// 		(1) && (count++, i++);
// 	if (count != 0)
// 	{
// 		str = malloc((count + 1) * sizeof(char *));
// 		ft_check_allocation(str);
// 	}
// 	return (str);
// }

// //!ft_check_if_chars_digit(var[i])
// char	*ft_fetch_word_from_env(t_env *env, char *arg)
// {
// 	t_env	*head;
// 	char	*tmp;
// 	char	*ptr;
// 	int		i;
// 	int		flag;

// 	(1) && (head = env, i = 0, flag = 0);
// 	ptr = NULL;
// 	(1) && (tmp = ft_trim_word(arg), tmp = ft_strjoin(tmp, "="));
// 	ft_check_allocation(tmp);
// 	while (head != NULL)
// 	{
// 		i = 0;
// 		while (tmp && tmp[i] == head->value[i])
// 			i++;
// 		if (head->value[i] == '=' && !ft_check_if_chars_digit(tmp[i]))
// 		{
// 			flag = 1;
// 			break ;
// 		}
// 		head = head->next;
// 	}
// 	if (head != NULL)
// 		ptr = ft_allocate_for_var(flag, head->value, i);
// 	return (ptr);
// }

// /*
// *	This function expands the variables for the here_doc
// */
// char	*ft_handle_expand_for_here_doc(t_env *env, char *arg)
// {
// 	char	*expanded;
// 	char	*ptr;
// 	int		start;
// 	int		i;

// 	i = 0;
// 	(1) && (expanded = NULL, ptr = NULL);
// 	while (arg && arg[i] != '\0')
// 	{
// 		start = i;
// 		while (arg[i] != '$')
// 			i++;
// 		ptr = ft_substr(arg, start, i - start);
// 		expanded = ft_fetch_word_from_env(env, arg + i);
// 	}
// 	return (expanded);
// }

static char	*ft_arg_is_exist(t_env *env, char *var)
{
	t_env	*head;
	char	*ptr;
	int		i;
	int		flag;

	(1) && (head = env, i = 0, flag = 0, ptr = NULL);
	while (head != NULL)
	{
		i = 0;
		while (var[i] == head->value[i])
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

static int	ft_expand_word_after_dollar_here_doc(t_expand *exp, int *i, \
	char *arg, t_env *env)
{
	if (ft_handle_inregulare_cases(exp, arg[(*i) + 1], i))
		return (1);
	exp->expa = ft_arg_is_exist(env, arg + (*i + 1));
	exp->s = exp->new_str;
	exp->new_str = ft_strjoin(exp->new_str, exp->expa);
	return (0);
}

/*
*	This function expands the variables
*/
char	*ft_handle_expand_for_here_doc(t_env *env, char *arg)
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
			if (ft_expand_word_after_dollar_here_doc(&exp, &i, arg, env))
				continue ;
			i += ft_surpass_chars(arg + (i + 1));
		}
		else if (arg[i])
			i++;
	}
	return (exp.new_str);
}
