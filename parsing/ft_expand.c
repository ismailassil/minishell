/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 20:44:38 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*ft_strjoin_(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*new_str;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	(1) && (len1 = ft_strlen(str1), len2 = ft_strlen(str2));
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	while (str1 && str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	while (str2 && str2[j])
	{
		new_str[i] = str2[j];
		(1) && (i++, j++);
	}
	new_str[i] = '\0';
	return (new_str);
}

int	handle_inregulare_cases(t_expand *exp, int c, int *i)
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
			exp->new_str = ft_strjoin_(s, "himBH");
			*i += 1;
			free(s);
		}
		else
			ft_append_char(&exp->new_str, '$');
		return ((*i += 1), 1);
	}
	return (0);
}

static char	*ft_handle_expand(t_env *env, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0);
	if (arg[i] == '\'' || arg[i] == '\"')
		(exp.quote = arg[i++]);
	while (arg[i] != '\0')
	{
		if ((arg[i] == '\'' || arg[i] == '\"'))
		{
			if (!exp.quote)
				exp.quote = arg[i++];
			else if (arg[i] == exp.quote)
				(1) && (i++, exp.quote = 0);
		}
		if (arg[i] && arg[i] == '$' && exp.quote != '\'')
		{
			if (handle_inregulare_cases(&exp, arg[i + 1], &i))
				continue ;
			exp.expa = ft_arg_is_exist(env, arg + (i + 1));
			exp.s = exp.new_str;
			exp.new_str = ft_strjoin(exp.new_str, exp.expa);
			i += ft_surpass_chars(arg + (i + 1));
		}
		else if (arg[i] && arg[i] != exp.quote)
			ft_append_char(&exp.new_str, arg[i++]);
	}
	return (exp.new_str);
}

void	ft_expand_argument(t_env *env, t_token **linked_list)
{
	t_token	*head;

	head = *linked_list;
	while (head != NULL)
	{
		if (ft_strchr(head->token, '$'))
			head->token = ft_handle_expand(env, head->token);
		head = head->next;
	}
}
