/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutli_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:48:38 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 21:12:29 by iassil           ###   ########.fr       */
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
	if (info->fd.outfile == 1)
	{
		ft_syscall(dup2(info->pipe[1], STDOUT_FILENO), "dup2 (PIPE)");
		ft_syscall(close(info->pipe[1]), "close");
	}
	else
	{
		ft_syscall(dup2(info->fd.outfile, STDOUT_FILENO), "dup2 (STDOUT)");
		ft_syscall(close(info->pipe[1]), "close");
	}
}

void	ft_child_process(t_cont *cont, t_env *env, t_info *info)
{
	t_execve	exec;
	char		**cmd;

	cmd = NULL;
	ft_syscall(close(info->pipe[0]), "pipe");
	if (ft_open_files(cont, &info->fd, env) == 1)
		exit(FAIL);
	ft_default_signals();
	ft_syscall(dup2(info->fd.infile, STDIN_FILENO), "dup2");
	if (info->fd.infile != 0)
		ft_syscall(close(info->fd.infile), "close");
	if (info->i == (info->nbr_cont - 1))
		ft_pipe_to_outfile(info);
	else
		ft_pipe_to_next_child(info);
	if (ft_check_commands(cont, env, info, 0) == 1)
		exit(env->status);
	ft_check_(&exec.cmd_path, cont->cmd, env);
	exec.argv = ft_join_for_argv_execve(cont);
	exec.envp = ft_join_for_envp_execve(env);
	if (execve(exec.cmd_path, exec.argv, exec.envp) == -1)
		(perror("msh: execve"), exit(FAIL));
}

void	ft_execute_child(t_cont *cont, t_env *env, t_info *info)
{
	while (info->i < info->nbr_cont)
	{
		ft_syscall(pipe(info->pipe), "pipe");
		info->id[info->i] = fork();
		ft_syscall(info->id[info->i], "fork");
		if (info->id[info->i] == 0)
			ft_child_process(cont, env, info);
		else
		{
			ft_syscall(close(info->pipe[1]), "close");
			if (info->fd.infile != 0)
				ft_syscall(close(info->fd.infile), "close");
			info->fd.infile = info->pipe[0];
		}
		info->i++;
		if (cont->next != NULL)
			cont = cont->next;
	}
}

void	ft_execute_multiple_cmds(t_cont *cont, \
	t_env *env, t_info *info, int nbr_cont)
{
	int		status;

	info->i = 0;
	(1) && (info->fd.infile = 0, info->fd.outfile = 1);
	info->nbr_cont = nbr_cont;
	if (cont == NULL)
		return ;
	if ((nbr_cont == 0 || nbr_cont == 1)
		&& (ft_open_files(cont, &info->fd, env) == 1
			|| ft_check_commands(cont, env, info, 1) == 1))
		return ;
	info->id = malloc(nbr_cont * sizeof(int));
	ft_check_allocation(info->id);
	ft_execute_child(cont, env, info);
	(ft_syscall(close(info->pipe[0]), "pipe"), free(info->id));
	info->i = 0;
	while (info->i++ < nbr_cont)
		waitpid(ALLCHILDS, &status, 0);
	env->status = WEXITSTATUS(status);
}
