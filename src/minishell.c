/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/24 22:15:03 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct termios	g_original_attr;

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(t_env *env, char *input)
{
	t_token	*head;
	char	*shell;

	(1) && (head = NULL, shell = ft_add_space_to_input(input));
	if (!ft_check_quotes(shell))
	{
		ft_error("msh: syntax error\n");
		env->status = 258;
		free(shell);
		return ;
	}
	ft_split_tokens(&head, shell);
	free(shell);
	ft_tokenize(&head);
	if (ft_check_syntax(head) == false)
	{
		if (ft_here_doc_parsing(head, env) == 0)
			ft_error("msh: syntax error\n");
		ft_free_tokens(&head);
		env->status = 258;
		return ;
	}
	(ft_remove_quotes(&head), ft_expand_argument(env, &head));
	ft_execution(&head, env);
}

// (ft_print_types(head), ft_print(head));
// void leaks()
// {
//     fclose(gfp);
//     system("leaks minishell");
//     usleep(1000 * 100 *10000);
// }
// 	gfp = fopen("leaks.t", "w");
// 	atexit(leaks);

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*envp;

	envp = NULL;
	((void)argc, (void)argv);
	ft_syscall(tcgetattr(STDIN_FILENO, &g_original_attr), "msh: tcgetattr");
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
	}
}
