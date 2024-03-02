/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 17:19:19 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(char *input)
{
	char	*shell;
	t_token	*head;

	head = NULL;
	shell = ft_add_space_to_input(input);
	init_tokens(&head, shell);
	while (head != NULL)
	{
		printf("%s\n", head->token);
		head = head->next;
	}
}

bool	ft_find_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'e' && line[i + 1] == 'x'
			&& line[i + 2] == 'i' && line[i + 3] == 't')
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
