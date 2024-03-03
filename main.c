/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:23:30 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/03 10:30:42 by aibn-che         ###   ########.fr       */
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
			count_quotes++;
			c = str[i++];
			while (str[i])
			{
				if (c == str[i])
					count_quotes++;
			}
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

int main(int argc, char** argv)
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
			printf("%s\n", head->token);
			head = head->next;
		}
		free(buf);
	}
	return (0);
}
