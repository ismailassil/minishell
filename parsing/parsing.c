/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musashi <musashi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:33:28 by iassil            #+#    #+#             */
/*   Updated: 2024/04/07 22:10:34 by musashi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stend	*ft_extract_start_end_of_token(char *str, int s)
{
	t_stend	*cord;
	int		i;
	int		c;

	cord = malloc(sizeof(t_stend));
	ft_check_allocation(cord);
	i = s;
	c = 0;
	cord->start = s;
	if (str[i] == '\'')
		(1) && (i++, c = '\'');
	else if (str[i] == '\"')
		(1) && (i++, c = '\"');
	while (!c && str[i] && !ft_strchr(" \t\n\v\f\r", str[i]))
		i++;
	while (c && str[i] && str[i] != c)
		i++;
	if (c == 0)
		i--;
	cord->end = i;
	return (cord);
}

char	*ft_alloc_str(t_token **tokens, char *str, t_stend *cord)
{
	int		len;
	int		i;
	char	*tk;

	(void)tokens;
	len = cord->end - cord->start;
	i = 0;
	tk = malloc(sizeof(char) * (len + 2));
	ft_check_allocation(tk);
	str += cord->start;
	while (cord->start <= cord->end)
	{
		tk[i] = str[i];
		cord->start++;
		i++;
	}
	tk[i] = '\0';
	return (tk);
}

static void	ft_parse_space_rest(char *input, char **shell, t_in *f)
{
	if (f->flag == 0 && (input[f->j] == '>' || input[f->j] == '<' \
		|| input[f->j] == '|' ))
	{
		(*shell)[f->i++] = ' ';
		(*shell)[f->i++] = input[f->j++];
		(*shell)[f->i++] = ' ';
	}
	else
	{
		(*shell)[f->i++] = input[f->j++];
		if (input[f->j] && f->tmp != f->j && input[f->j] == f->quote)
		{
			(*shell)[f->i++] = input[f->j++];
			f->flag = 0;
			f->quote = 0;
		}
	}
}

static void	*ft_parse_space(char *input, char **shell)
{
	t_in	f;

	(1) && (f.i = 0, f.flag = 0, f.quote = 0, f.j = 0);
	while (input[f.j] != 0)
	{
		if (input[f.j] == '\"' || input[f.j] == '\'')
			(1) && (f.tmp = f.j, f.flag = 1, f.quote = input[f.j]);
		if (f.flag == 0 && ((input[f.j] == '>' && input[f.j + 1] == '>') \
			|| (input[f.j] == '<' && input[f.j + 1] == '<')))
		{
			(*shell)[f.i++] = ' ';
			(*shell)[f.i++] = input[f.j++];
			(*shell)[f.i++] = input[f.j++];
			(*shell)[f.i++] = ' ';
		}
		else
			ft_parse_space_rest(input, shell, &f);
	}
	(*shell)[f.i] = '\0';
	return (shell);
}

/*	This function add spaces between the operators
*	[{ > outfile}, { < infile}, { >> append}, {<< heredoc}, { | pipe}]
*	like: [ls>file1|grep pipex] ==> [ ls > fil1 | grep pipex ]
*/
char	*ft_add_space_to_input(char *input)
{
	char	*shell;
	t_in	inf;

	(1) && (inf.i = 0, inf.flag = 0, inf.quote = 0, inf.count = 0);
	while (input[inf.i] != '\0')
	{
		if (input[inf.i] == '\"' || input[inf.i] == '\'')
		{
			inf.flag = 1;
			inf.quote = input[inf.i];
		}
		if (inf.flag == 0 && ((input[inf.i] == '>' && input[inf.i + 1] == '>') \
			|| (input[inf.i] == '<' && input[inf.i + 1] == '<')))
			(1) && (inf.count++, inf.i++);
		else if (inf.flag == 0 && (input[inf.i] == '>' \
			|| input[inf.i] == '<' || input[inf.i] == '|'))
			inf.count++;
		if (input[inf.i] != '\0' && input[inf.i] == inf.quote)
			inf.flag = 0;
		inf.i++;
	}
	shell = (char *)malloc((inf.i + 1 + (inf.count * 2)) * sizeof(char));
	if (!shell)
		exit(EXIT_FAILURE);
	ft_parse_space(input, &shell);
	return (shell);
}
