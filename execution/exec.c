/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 15:43:03 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2(t_fd *fd)
{
	if (dup2(fd->infile, STDIN_FILENO) == -1)
		(perror("dup2 (STDIN)"), exit(EXIT_FAILURE));
	if (fd->infile != 0)
		close(fd->infile);
	if (dup2(fd->outfile, STDOUT_FILENO) == -1)
		(perror("dup2 (STDOUT)"), exit(EXIT_FAILURE));
	if (fd->outfile != 1)
		close(fd->outfile);
}

int	ft_execute_one_cmd(t_cont *cont, t_env *env)
{
	t_execve	exec;
	t_fd		fd;
	pid_t		id;

	if (cont == NULL)
		return (1);
	if (ft_open_files(cont, &fd) == 1 || ft_check_commands(cont, env) == 1)
		return (1);
	id = fork();
	ft_syscall(id, "fork");
	if (id == 0)
	{
		ft_default_signals();
		ft_dup2(&fd);
		ft_check_(&exec.cmd_path, cont->cmd, env);
		exec.argv = ft_join_for_argv_execve(cont);
		exec.envp = ft_join_for_envp_execve(env);
		if (execve(exec.cmd_path, exec.argv, exec.envp) == -1)
			(perror("msh: execve"), exit(FAIL));
	}
	wait(CHILD);
	return (0);
}

void	ft_execution(t_token **token, t_env *env)
{
	t_token			*head;
	t_cont			*container;
	unsigned int	nbr_cmd;

	head = *token;
	nbr_cmd = 0;
	while (head)
	{
		if (head->type == CMD)
			nbr_cmd++;
		head = head->next;
	}
	ft_link_all_in_containers(*token, &container);
	// ft_print_container(container);
	if (nbr_cmd == 1 || nbr_cmd == 0)
		ft_execute_one_cmd(container, env);
	else if (nbr_cmd > 1)
		ft_execute_multiple_cmds(container, env, nbr_cmd);
	ft_free_containers(&container);
}
