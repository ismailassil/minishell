/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:00:00 by iassil            #+#    #+#             */
/*   Updated: 2024/04/26 16:01:58 by iassil           ###   ########.fr       */
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
		while (str[i] && ft_strchr(" \t\n\v\f\r", str[i]))
			i++;
		if (!str[i])
			break ;
		cord = ft_extract_start_end_of_token(str, i);
		token = ft_alloc_str(head, str, cord);
		ft_push_token(token, head);
		i = cord->end;
		free(cord);
		while (str[i] && ft_strchr(" \t\n\v\f\r", str[i]))
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
	ft_check_allocation(*str);
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

/*
*	Define the quote,
*	that should not be included within the string
*/
void	ft_update_quote(char *arg, int *i, t_expand *exp)
{
	if (exp->quote == arg[*i])
	{
		exp->quote = 0;
		arg[*i] = SQ;
	}
	else if (!exp->quote)
	{
		exp->quote = arg[*i];
		arg[*i] = SQ;
	}
	else
	{
		ft_append_char(&exp->new_str, arg[*i]);
		(*i)++;
	}
}

void	ft_error(char *str)
{
	if (str != NULL)
		write(2, str, ft_strlen(str));
}
