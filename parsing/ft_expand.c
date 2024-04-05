/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/04/05 03:16:44 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	Checks if the expanded variable exists in the env
*/
char	*ft_arg_is_exist(t_env *env, char *var)
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

int	ft_between_bracket(char *str, int i)
{
	int	n;

	n = 0;
	if (str && str[i] == '{')
		n++;
	while (str && str[i])
	{
		if (str[i] == '}')
		{
			n++;
			break ;
		}
		i++;
	}
	if (n == 2)
		return (i + 1);
	return (0);
}

/*
*	This function expands the variables
*/
char	*ft_handle_expand(t_struct *strp, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0, exp.quote = 0);
	if (arg[i] == '\'' || arg[i] == '\"')
		(exp.quote = arg[i++]);
	while (arg[i] != '\0')
	{
		if ((arg[i] == '\'' || arg[i] == '\"'))
			ft_update_quote(arg, &i, &exp);
		else if (arg[i] && arg[i] != exp.quote && arg[i] != '$')
			ft_append_char(&exp.new_str, arg[i++]);
		else if (arg[i] && arg[i] == '$')
		{
			if (ft_expand_word_after_dollar(&exp, &i, arg, strp))
				continue ;
			i += ft_surpass_chars(arg + (i + 1));
		}
		else if (arg[i])
			i++;
	}
	return (exp.new_str);
}

/*
*	This function expands the Variables from the env
*/
void	ft_expand_argument(t_struct *strp, t_token **linked_list)
{
	t_expand_arg	f;

	(1) && (f.head = *linked_list, f.tmp = NULL, f.previous = NULL);
	while (f.head != NULL)
	{
		if (f.head->type == CMD)
		{
			if (ft_strncmp(f.head->token, "export", 5) == 0)
				f.type = 1;
			else
				f.type = 0;
		}
		if (ft_strchr(f.head->token, '$') && f.head->type != DELIMITER)
		{
			f.head->is_var = 1;
			if (ft_strchr(f.head->token, '"'))
				f.head->is_quote = 1;
			f.tmp = ft_handle_expand(strp, f.head->token);
			free(f.head->token);
			f.head->token = f.tmp;
			if (ft_check_after_expand(&f.head, f.head->is_quote) == 1)
				ft_split_node(&f, linked_list);
		}
		f.previous = f.head;
		if (f.head)
			f.head = f.head->next;
	}
}
