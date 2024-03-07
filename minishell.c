/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 16:57:54 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(t_env *env, char *input)
{
	char	*shell;
	t_token	*head;

	head = NULL;
	shell = ft_add_space_to_input(input);
	ft_split_pro_max(&head, shell);
	free(shell);
	ft_tokenize(&head);
	if (ft_check_syntax(head) == false)
		return ;
	// (void)env;
	ft_expand_argument(env, &head);
	// ft_remove_quotes(&head);
		ft_print_types(head);
		ft_print(head);
	// ft_execution(&head);
}

// void	v(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*envp;

	// atexit(v);
	// ft_signal_handler();
	((void)argc, (void)argv);
	envp = NULL;
	envp = ft_get_env(env);
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
		ft_parse_input_from_shell(envp, line);
		free(line);
		printf("\n");
	}
}
