/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutli_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:48:38 by iassil            #+#    #+#             */
/*   Updated: 2024/03/19 01:02:27 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipe_to_outfile(t_info *info)
{
	ft_syscall(dup2(info->fd.outfile, STDOUT_FILENO), "dup2 (STDOUT)");
	if (info->fd.outfile != 1)
		ft_syscall(close(info->fd.outfile), "close");
	ft_syscall(close(info->pipe[1]), "close");
}

static void	ft_pipe_to_next_child(t_info *info)
{
	ft_syscall(dup2(info->pipe[1], STDOUT_FILENO), "dup2 (PIPE)");
	ft_syscall(close(info->pipe[1]), "close");
	if (info->fd.outfile != 1)
		ft_syscall(close(info->fd.outfile), "close");
}

void	ft_child_process(t_cont *cont, t_env *env, t_info *info)
{
	t_execve	exec;
	char		**cmd;

	cmd = NULL;
	ft_syscall(close(info->pipe[0]), "pipe");
	if (ft_open_files(cont, &info->fd, env))
		exit(FAIL);
	ft_default_signals();
	ft_syscall(dup2(info->fd.infile, STDIN_FILENO), "dup2");
	if (info->fd.infile != 0)
		ft_syscall(close(info->fd.infile), "close");
	if (info->i == (info->nbr_cmd - 1))
		ft_pipe_to_outfile(info);
	else
		ft_pipe_to_next_child(info);
	if (ft_check_commands(cont, env) == 1)
		exit(FAIL);
	ft_check_(&exec.cmd_path, cont->cmd, env);
	exec.argv = ft_join_for_argv_execve(cont);
	exec.envp = ft_join_for_envp_execve(env);
	if (execve(exec.cmd_path, exec.argv, exec.envp) == -1)
		(perror("msh: execve"), exit(FAIL));
}

void	ft_execute_multiple_cmds(t_cont *cont, t_env *env, int nbr_cmd)
{
	int		i;
	pid_t	*id;
	t_info	info;
	int		status;

	i = 0;
	id = malloc(nbr_cmd * sizeof(int));
	ft_check_allocation(id);
	(1) && (info.nbr_cmd = nbr_cmd, info.fd.infile = 0, info.fd.outfile = 1);
	while (i < nbr_cmd)
	{
		ft_syscall(pipe(info.pipe), "pipe");
		info.i = i;
		id[i] = fork();
		ft_syscall(id[i], "fork");
		if (id[i] == 0)
			ft_child_process(cont, env, &info);
		else
		{
			ft_syscall(close(info.pipe[1]), "close");
			if (info.fd.infile != 0)
				ft_syscall(close(info.fd.infile), "close");
			info.fd.infile = info.pipe[0];
		}
		i++;
		if (cont->next != NULL)
			cont = cont->next;
	}
	(ft_syscall(close(info.pipe[0]), "pipe"), free(id));
	i = 0;
	while (i++ < nbr_cmd)
		waitpid(ALLCHILDS, &status, 0);
	env->status = WEXITSTATUS(status);
}
