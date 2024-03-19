/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 23:23:51 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(t_env *env, char *input)
{
	t_token	*head;
	char	*shell;

	head = NULL;
	shell = ft_add_space_to_input(input);
	if (!ft_check_quotes(shell))
	{
		ft_error("msh: parse error\n");
		return ;
	}
	ft_split_tokens(&head, shell);
	free(shell);
	ft_tokenize(&head);
	if (ft_check_syntax(head) == false)
		return ;
	ft_remove_quotes(&head);
	ft_expand_argument(env, &head);
	ft_print_types(head);
	ft_print(head);
	ft_execution(&head, env);
	ft_free_tokens(&head);
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
	envp = NULL;
	((void)argc, (void)argv);
	ft_signal_handler();
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
		printf(BLUE"[status ($?) = %d]\n"RESET, envp->status);
		// printf("\n");
	}
}
