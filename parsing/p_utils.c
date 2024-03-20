/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:00:00 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 14:14:06 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_tokens(t_token **head, char *str)
{
	int		i;
	char	*token;
	t_stend	*cord;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		cord = ft_extract_start_end_of_token(str, i);
		token = ft_alloc_str(head, str, cord);
		ft_push_token(token, head);
		i = cord->end;
		free(cord);
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		i++;
	}
}

void	ft_append_char(char **str, int c)
{
	int		len;
	char	*s;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	s = *str;
	*str = malloc(sizeof(char) * (len + 2));
	if (!(*str))
		return ;
	while (s && s[i])
	{
		(*str)[i] = s[i];
		i++;
	}
	(1) && ((*str)[i++] = c, (*str)[i] = '\0');
	free(s);
}

char	*ft_allocate_for_var(int flag, char *str, int i)
{
	char	*ptr;

	ptr = NULL;
	if (flag == 1 && str != NULL)
	{
		str += (i + 1);
		ptr = ft_strdup(str);
		if (!ptr)
			return (NULL);
		str -= (i + 1);
		return (ptr);
	}
	return (ptr);
}

int	ft_handle_inregulare_cases(t_expand *exp, int c, int *i)
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

/*
*	Define the quote,
*	that should not be included within the string
*/
void	ft_update_quote(char *arg, int *i, t_expand *exp)
{
	if (exp->quote == arg[*i])
	{
		exp->quote = 0;
		(*i)++;
	}
	else if (!exp->quote)
	{
		exp->quote = arg[*i];
		(*i)++;
	}
	else
	{
		ft_append_char(&exp->new_str, arg[*i]);
		(*i)++;
	}
}
