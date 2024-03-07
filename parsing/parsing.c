/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:33:28 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 16:44:03 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_split_pro_max(t_token **head, char *str)
{
	t_stend	*cord;
	char	*token;
	char	*whitespaces;
	int		quote;
	int		i;

	i = 0;
	whitespaces = " \t\n\v\f\r";
	while (str[i])
	{
		while (str[i] && ft_strchr(whitespaces, str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				quote = str[i];
				while (str[i] != quote && str[i])
					i++;
			}
			i++;
		}
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
