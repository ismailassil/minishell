/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:33:28 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 00:40:25 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stend	*ft_extract_start_end_of_token(char *str, int s)
{
	t_stend	*cord;
	int		i;
	int		c;

	cord = malloc(sizeof(t_stend));
	if (!cord)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
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

char	*ft_alloc_str(t_token **tokens, char *str, t_stend *cord)
{
	int		len;
	int		i;
	char	*tk;

	(void)tokens;
	len = cord->end - cord->start;
	i = 0;
	tk = malloc(sizeof(char) * (len + 2));
	if (!tk)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
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

static void	*ft_parse_space(char *input, char **shell)
{
	int	i;
	int	j;
	int	flag;
	int	quote;
	int	tmp;

	(1) && (i = 0, flag = 0, quote = 0, j = 0);
	while (input[j] != 0)
	{
		if (input[j] == '\"' || input[j] == '\'')
			(1) && (tmp = j, flag = 1, quote = input[j]);
		if (flag == 0 && ((input[j] == '>' && input[j + 1] == '>') || (input[j]  == '<'
			&& input[j + 1] == '<')))
		{
			(*shell)[i] = ' ';
			(*shell)[i + 1] = input[j];
			(*shell)[i + 2] = input[j + 1];
			(*shell)[i + 3] = ' ';
			i += 4;
			j += 2;
		}
		else if (flag == 0 && (input[j] == '>' || input[j] == '<' || input[j] == '|' ))
			(1) && ((*shell)[i] = ' ', (*shell)[i + 1] = input[j], \
				(*shell)[i + 2] = ' ', i += 3, j++);
		else
		{
			(1) && ((*shell)[i] = input[j], i++, j++);
			if (input[j] && tmp != j && input[j] == quote)
				(1) && ((*shell)[i] = input[j], i++, j++, flag = 0, quote = 0);
		}
	}
	(*shell)[i] = '\0';
	return (shell);
}

/*	This function add spaces between the operators
*	[{ > outfile}, { < infile}, { >> append}, {<< heredoc}, { | pipe}]
*	like: [ls>file1|grep pipex] ==> [ ls > fil1 | grep pipex ]
*/
char	*ft_add_space_to_input(char *input)
{
	int		i;
	int		count;
	int		flag;
	int		quote;
	char	*shell;

	(1) && (i = 0, flag = 0, quote = 0, count = 0);
	while (input[i] != '\0')
	{
		if (input[i] == '\"' || input[i] == '\'')
			(1) && (flag = 1, quote = input[i]);
		if (flag == 0 && ((input[i] == '>' && input[i + 1] == '>') || (input[i]  == '<'
			&& input[i + 1] == '<')))
			count++;
		else if (flag == 0 && (input[i] == '>' || input[i] == '<' || input[i] == '|'))
			count++;
		i++;
		if (input[i] != '\0' && input[i] == quote)
			(1) && (flag = 0, i++);
	}
	shell = (char *)malloc((i + 1 + (count * 2)) * sizeof(char));
	if (!shell)
		exit(EXIT_FAILURE);
	ft_parse_space(input, &shell);
	return (shell);
}
