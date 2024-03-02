/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 15:29:46 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>

/*	Checks if there is any space char	*/
bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

/*	Checks if there is any special char	*/
bool	ft_special_char(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

/*	Print the data in the Linked list imported from the shell	*/
void	ft_print(t_container *lst)
{
	t_container	*head = lst;

	while (head != NULL)
	{
		printf("====={%s}=====\n", head->holder);
		head = head->next;
	}
}

/*	Add the input from shell to linked list	*/
void	ft_add_holder_to_container(t_container	**spart, char *input, int i, int index)
{
	char		*tmp;
	t_container	*holder;

	tmp = ft_substr(input, i - index, index);
	holder = ft_lstnew(tmp);
	if (holder == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(spart, holder);
	// printf("===={%s}====\n", holder->holder);
}

char	*ft_add_space_to_input(char *input)
{
	int			i;
	int			j;
	int			count;
	char		*shell;

	(1) && (i = 0, count = 0);
	while (input[i] != '\0')
	{
		if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
			(count++);
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			(count++);
		i++;
	}
	shell = (char *)malloc((i + 1 + (count * 2)) * sizeof(char));
	if (!shell)
		exit(EXIT_FAILURE);
	(1) && (i = 0, j = 0);
	while (input[j] != 0)
	{
		if ((input[j] == '>' && input[j + 1] == '>') || (input[j] == '<' && input[j + 1] == '<'))
		{
			shell[i] = ' ';
			shell[i + 1] = input[j];
			shell[i + 2] = input[j + 1];
			shell[i + 3] = ' ';
			i += 4;
			j += 2;
		}
		else if (input[j] == '>' || input[j] == '<' || input[j] == '|' )
			(shell[i] = ' ', shell[i + 1] = input[j], shell[i + 2] = ' ', i += 3, j++);
		else
			(shell[i] = input[j], i++, j++);
	}
	shell[i] = '\0';
	return (shell);
}

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(char *input)
{
	char	*shell;

	shell = ft_add_space_to_input(input);
	printf("======={%s}=======\n", shell);
}

bool	ft_find_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'i' && line[i + 3] == 't')
			return (true);
		i++;
	}
	return (false);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	((void)argc, (void)argv, (void)env);
	ft_signal_handler();
	while (true)
	{
		line = readline(YELLOW"minishell$ "RESET);
		if (line == NULL || ft_find_exit(line) == true)
			ft_exit();
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parse_input_from_shell(line);
		free(line);
	}
}
