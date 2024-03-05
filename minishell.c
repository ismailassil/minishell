/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 10:19:15 by iassil           ###   ########.fr       */
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
	ft_tokenize(&head);
	ft_print_types(head);
	ft_check_syntax(head);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	((void)argc, (void)argv, (void)env);
	// ft_signal_handler();
	while (true)
	{
		line = readline(YELLOW_"minishell$ "RESET);
		if (line == NULL)
		{
			if (line == NULL)
				printf("exit\n");
			ft_exit();
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parse_input_from_shell(line);
		free(line);
		printf("\n");
	}
}
