/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:21:04 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 15:48:43 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	This function will search and return
*	the token indicated in the parameters	*/
int	ft_gettoken(char **ps, char *es, char *q, char *eq)
{
	char	*s;
	char	*whitespace;
	char	*symbols;
	int		ret;

	whitespace = " \t\n\v\r\f";
	symbols = "<|>";
	s = *ps;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	if (q)
		q = s;
	if (*s == '|')
		ret = PIPE;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
			(1) && (ret = GGREAT, s++);
	}
	else if (*s == '>')
	{
		s++;
		if (*s == '<')
			ret = HEREDOC;
	}
	else
	{
		ret = 0;
		while (s < es && !ft_strchr(whitespace, *s) && !ft_strchr(symbols, *s))
			s++;
	}
	if (eq)
		eq = s;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	*ps = s;
	return (ret);
}
