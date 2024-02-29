/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/02/29 17:12:35 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (c == '>' || c == '<' || c == '|' || c == '\'' || c == '\"')
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

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(char *input)
{
	int			i;
	int			index;
	t_container	*spart;

	spart = NULL;
	(1) && (i = 0, index = 0);
	while (input[i] != '\0')
	{
		while (ft_isspace(input[i]) == true && input[i] != '\0')
			i++;
		while (ft_isspace(input[i]) == false && ft_special_char(input[i]) == false && input[i] != '\0')
			(index++, i++);
		ft_add_holder_to_container(&spart, input, i, index);
	}
	ft_print(spart);
}

/*	Read the line from the shell using the readline function	*/
void	ft_get_input(void)
{
	char	*line;

	while (true)
	{
		line = readline(YELLOW"minishell$ "RESET);
		if (line == NULL)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parse_input_from_shell(line);
		free(line);
	}
}

int	main(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_d;
	struct sigaction	ctrl__;

	ctrl_c.sa_handler = ctrl_c_handler;
	ctrl_d.sa_handler = ctrl_d_handler;
	ctrl__.sa_handler = ctrl___handler;
	// if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
	// 	(perror("Error"), exit(EXIT_FAILURE));
	// if (sigaction(SIGTERM, &ctrl_d, NULL) == -1)
	// 	(perror("Error"), exit(EXIT_FAILURE));
	// if (sigaction(SIGQUIT, &ctrl__, NULL) == -1)
	// 	(perror("Error"), exit(EXIT_FAILURE));
	ft_get_input();
}
