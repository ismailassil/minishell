/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:23:30 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/05 10:25:48 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_stend	*extract_start_end_of_token(char *str, int *s)
{
	t_stend	*cord;
	int		i;
	int		c;

	cord = malloc(sizeof(t_stend));
	i = *s;
	c = 0;
	cord->start = *s;
	if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != ' ')
			i++;
		*s = i;
		cord->end = --i;
		return (cord);
	}
	if (str[i] == '<' || str[i] == '>')
	{
		i++;
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != ' ')
			i++;
		*s = i;
		cord->end = --i;
		return (cord);
	}
	else if (str[i] == '|')
	{
		cord->end = i;
		*s = ++i;
		return (cord);
	}
	else
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
			i++;
	}
	*s = i;
	cord->end = --i;
	return (cord);
}

char	*alloc_str(t_token **tokens, char *str, t_stend *cord)
{
	int		len;
	int		i;
	char	*tk;

	len = cord->end - cord->start;
	i = 0;
	tk = malloc(sizeof(char) * (len + 1 + 1));
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
		cord = extract_start_end_of_token(str, &i);
		token = alloc_str(head, str, cord);
		push(token, head);
		free(cord);
	}
}

int	check_quotes(char *str)
{
	int	i;
	int	count_quotes;
	int	c;

	count_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			count_quotes++;
			while (str[i])
			{
				if (c == str[i])
					count_quotes++;
				i++;
			}
			if (str[i] == '\0')
				break ;
		}
		i++;
	}
	if ((count_quotes % 2) == 0)
		return (1);
	return (0);
}

t_tree	*create_node_tree(char *cmd)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	print_tree(t_tree *node)
{
	if (!node)
		return ;
	printf("%s\n",node->cmd);
	//left
	print_tree(node->left);
	//right
	print_tree(node->right);
}

void	insert_tree(t_tree *tr, char *str)
{
	
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_cmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && (str1[i] == str2[i]))
		i++;
	if (str_len(str1) > str_len(str2) && str1[i] == ' ')
		return (0);
	return (str1[i] - str2[i]);
}

int	check_if_chars_digit(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*var_is_exist(char **env, char *var)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (var[j] == env[i][j])
		{
			j++;
		}
		if (env[i][j] == '=' && !check_if_chars_digit(var[j]))
			break ;
		i++;
	}
	if (env[i])
	{
		env[i]+=(j + 1);
		printf("%s", env[i]);
		env[i]-=(j + 1);
		return ("yes");
	}
	return (NULL);
}

int	surpass_chars(char **env, char *var)
{
	int	i;

	i = 0;
	while (var[i] && check_if_chars_digit(var[i]))
	{
		i++;
	}
	return (i + 1);
}

// int	update_c(char *str, int i, int c)
// {
// 	int	cc;

// 	if (str[i] == '\'' || str[i] == '\"')
// 	{
// 		cc = str[i];
// 		while (c == 0 && i >= 0)
// 		{
// 			i--;
// 			if (str[i] == '\"' || str[i] == '\'')
// 				c = 
// 		}
		
// 		i++;
// 		while (c != 0 && str[i])
// 		{
// 			if (str[i] == '\'' || str[i] == '\"')
// 				return (str[i]);
// 			i++;
// 		}
// 	}
// 	return (0);
// }
//t_env*

////////////////////////ECHO/////////////////////////////////////////////////
void	handle_echo(char **env, char *token)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	i = 4;

	while (token[i] == ' ')
		i++;
	if (token[i] == '\'' || token[i] == '\"')
		c = token[i++];
	while (token[i])
	{
		if (token[i] == c)
			i++;
		if (!token[i])
			break ;
		if (token[i] == '$' && token[i - 1] != '\'')
		{
			if (var_is_exist(env, token + (i + 1)))
				(i += surpass_chars(env, token + (i + 1)));
			else
			{
				(i += surpass_chars(env, token + (i + 1)));
				i++;
			}
		}
		if (!token[i])
			break ;
		while (token [i] && token[i] == ' ' && token[i + 1] == ' ')
			i++;
		if (token[i] != c)
		{
			if (c == 0 && (token[i] == '\'' || token[i] == '\"'))
				;
			else
				printf("%c", token[i]);
		}
		i++;
	}
	printf("\n");
}
////////////////////////ECHO/////////////////////////////////////////////////

int main(int argc, char** argv, char **env)
{
	t_token	*head;

	head = NULL;
	int	i;
	i = 0;

	char	*buf;

	while (1)
	{
		buf = readline("minishell$ ");
		if (strlen(buf) > 0)
		{
			add_history(buf);
		}
		init_tokens(&head, buf);
		while (head)
		{
			if (!check_quotes(head->token))
				(printf("invalid quotes\n"), exit(0));
			if (!str_cmp(head->token, "echo"))
			{
				handle_echo(env, head->token);
			}
			head = head->next;
		}
		free(buf);
	}
	return (0);
}
