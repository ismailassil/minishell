/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutli_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:48:38 by iassil            #+#    #+#             */
/*   Updated: 2024/04/22 13:34:48 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipe_to_outfile(t_info *info)
{
	ft_syscall(dup2(info->fd.outfile, STDOUT_FILENO), "msh: dup2 (STDOUT)");
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

static void	ft_child_process(t_cont *cont, t_struct *strp, t_info *info)
{
	t_execve	exec;
	char		**cmd;

	cmd = NULL;
	ft_syscall(close(info->pipe[0]), "close");
	if (ft_open_files(cont, info, strp) == 1)
		(ft_exitf(&strp, &cont), exit(FAIL));
	ft_default_signals();
	ft_syscall(dup2(info->fd.infile, STDIN_FILENO), "dup2");
	if (info->fd.infile != 0)
		ft_syscall(close(info->fd.infile), "close");
	if (info->i == (info->nbr_cont - 1))
		ft_pipe_to_outfile(info);
	else
		ft_pipe_to_next_child(info);
	strp->nr_cont = info->nbr_cont;
	if (ft_check_commands(cont, strp, info, 0) == 1)
		(ft_exitf(&strp, &cont), exit(strp->status));
	ft_check_(&exec.cmd_path, &cont->cmd, strp, cont);
	exec.argv = ft_join_for_argv_execve(cont);
	exec.envp = ft_join_for_envp_execve(strp->env);
	(ft_exitf(&strp, &cont), free(strp));
	if (execve(exec.cmd_path, exec.argv, exec.envp) == -1)
		(ft_f(exec.argv), ft_f(exec.envp), ft_error("msh: "),
			perror(exec.cmd_path), free(exec.cmd_path), exit(126));
}

void	ft_execute_child(t_cont *cont, t_struct *strp, t_info *info)
{
	while (info->i < info->nbr_cont)
	{
		ft_syscall(pipe(info->pipe), "pipe");
		info->id[info->i] = fork();
		ft_syscall(info->id[info->i], "fork");
		if (info->id[info->i] == 0)
			ft_child_process(cont, strp, info);
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
	t_struct *strp, t_info *info, int nr_cont)
{
	int		status;

	info->i = 0;
	(1) && (info->fd.infile = 0, info->fd.outfile = 1);
	info->nbr_cont = nr_cont;
	if (ft_check_cont_and_cmd(cont, strp, info, nr_cont) == 1)
		return ;
	info->id = malloc(nr_cont * sizeof(int));
	ft_check_allocation(info->id);
	ft_execute_child(cont, strp, info);
	(ft_syscall(close(info->pipe[0]), "close"));
	info->i = 0;
	while (info->i < nr_cont)
		waitpid(info->id[info->i++], &status, 0);
	strp->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		strp->status = 131;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		strp->status = 130;
	ft_add_cmd_or_arg_to_env(nr_cont, cont, strp);
	free(info->id);
}
