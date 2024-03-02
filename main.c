/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:23:30 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/02 15:38:54 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	quote = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if(str[i] == 39 || str[i] == 34)
		{
			//single qoute
			if (str[i] == 39)
			{
				i++;
				if (str[i] != 39)
					count++;
				while (str[i] && str[i] != 39)
					i++;
				if (str[i] == 39)
					i++;
			}
			//double qoute
			else
			{
				i++;
				if (str[i] != 34)
					count++;
				while (str[i] && str[i] != 34)
					i++;
				if (str[i] == 34)
					i++;
			}
		}
		else
		{
			count++;
			while (!(str[i] == c) && str[i])
				i++;
		}
		while (str[i] && str[i] == c)
			i++;
	}
	return (count);
}

// t_stend	*extract_start_end_of_token(char *str, int s)
// {
// 	t_stend	*cord;
// 	int		i;
// 	int		c;

// 	cord = malloc(sizeof(t_stend));
// 	i = s;
// 	c = 0;
// 	cord->start = s;
// 	if (str[i] == '<' || str[i] == '>')
// 		i++, c = '\'';
// 	else if (str[i] == '\"')
// 		i++, c = '\"';
// 	while (!c && str[i] && str[i] != ' ')
// 		i++;
// 	while (c && str[i] && str[i] != c)
// 		i++;
// 	if (c == 0)
// 		i--;
// 	cord->end = i;
// 	return (cord);
// }
/**
 * < infile | grep "struct" | echo "hello 'ddd'"
 * 
*/
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
		i++, c = '\'';
	else if (str[i] == '\"')
		i++, c = '\"';
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

	len = cord->end - cord->start;
	i = 0;
	tk = malloc(sizeof(char) * (len + 1));
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

void init_tokens(t_token **head, char *str)
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
		push(token, head);
		i = cord->end;
		free(cord);
		while (str[i] && str[i] == ' ')
			i++;
		i++;
	}
}

int main(int argc, char** argv)
{
	t_token	*head;

	head = NULL;
	// char *str = "echo 'hello111   ''  $USER       ls'     '' |     echo '      amigo  '     ";

	// init_tokens(&head, str);
	// while (head)
	// {
	// 	printf("%s\n", head->token);
	// 	head = head->next;
	// }
	// t_stend *cord = extract_start_end_of_token(str, 5);
	// printf("start index is %d  |  end index is %d \n", cord->start, cord->end);
	// char *ss = alloc_str(&head, str, cord);
	// printf("final token = %s\n", ss);
	// init_tokens(&head);
	// char *str = "echo    'hello     world'''";
	// char *str = "ls> ls";
	// char *str = "echo    'hello     world' '' ";
	// char *str = "echo    'hello          world' '' ";
	// char *str = echo "hello world''""";
	// printf("%d\n", count_words(str, ' '));
	int	i;
	i = 0;
	// char **arr = ft_split(str, ' ');
	// while (arr[i])
	// 	printf("%s\n", arr[i++]);
	char	*buf;
	while (1)
	{
		buf = readline("minishell$ ");
		if (strlen(buf) > 0)
		{
			add_history(buf);
		}
		// printf("%s\n", buf);
		init_tokens(&head, buf);
		while (head)
		{
			printf("%s\n", head->token);
			head = head->next;
		}
		free(buf);
	// 	printf("[%s]\n", buf);
	// 	// readline malloc's a new buffer every time.
	// 	free(buf);
	}
	return (0);
}
