/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:33:28 by iassil            #+#    #+#             */
/*   Updated: 2024/03/03 19:28:33 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stend	*extract_start_end_of_token(char *str, int s)
{
	t_stend	*cord;
	int		i;
	int		c;

	cord = malloc(sizeof(t_stend));
	i = s;
	c = 0;
	cord->start = s;
	if (str[i] == '\'')
		(1) && (i++, c = '\'');
	else if (str[i] == '\"')
		(1) && (i++, c = '\"');
	while (!c && str[i] && str[i] != ' ')
		i++;
	while (c && str[i] && str[i] != c)
		i++;
	if (c == 0)
		i--;
	cord->end = i;
	return (cord);
}

char	*alloc_str(t_token **tokens, char *str, t_stend *cord)
{
	int		len;
	int		i;
	char	*tk;

	(void)tokens;
	len = cord->end - cord->start;
	i = 0;
	tk = malloc(sizeof(char) * (len + 2));
	if (!tk)
		return (NULL);
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

void	init_tokens(t_token **head, char *str)
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
		cord = extract_start_end_of_token(str, i);
		token = alloc_str(head, str, cord);
		ft_push_token(token, head);
		i = cord->end;
		free(cord);
		while (str[i] && str[i] == ' ')
			i++;
		i++;
	}
}

static void	*ft_parse_space(char *input, char **shell)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	while (input[j] != 0)
	{
		if ((input[j] == '>' && input[j + 1] == '>')
			|| (input[j] == '<' && input[j + 1] == '<'))
		{
			(*shell)[i] = ' ';
			(*shell)[i + 1] = input[j];
			(*shell)[i + 2] = input[j + 1];
			(*shell)[i + 3] = ' ';
			i += 4;
			j += 2;
		}
		else if (input[j] == '>' || input[j] == '<' || input[j] == '|' )
			(1) && ((*shell)[i] = ' ', (*shell)[i + 1] = input[j], \
				(*shell)[i + 2] = ' ', i += 3, j++);
		else
			(1) && ((*shell)[i] = input[j], i++, j++);
	}
	(*shell)[i] = '\0';
	return (shell);
}

char	*ft_add_space_to_input(char *input)
{
	int			i;
	int			count;
	char		*shell;

	(1) && (i = 0, count = 0);
	while (input[i] != '\0')
	{
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
			(count++);
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			(count++);
		i++;
	}
	shell = (char *)malloc((i + 1 + (count * 2)) * sizeof(char));
	if (!shell)
		exit(EXIT_FAILURE);
	ft_parse_space(input, &shell);
	return (shell);
}
