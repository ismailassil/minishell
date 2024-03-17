/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/17 17:24:12 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_files(t_cont *cont, t_fd *fd)
{
	int	i;
	int	fd_infile[OPEN_MAX];
	int	fd_outfile[OPEN_MAX];

	(1) && (i = -1, fd->infile = 0);
	while (cont->infile && cont->infile[++i] != 0)
	{
		fd_infile[i] = open(cont->infile[i], O_RDONLY);
		fd->infile = fd_infile[i];
		if (fd_infile[i] == -1)
			return (perror(cont->infile[i]), 1);
	}
	(1) && (i = -1, fd->outfile = 1);
	while (cont->outfile && cont->outfile[++i] != 0)
	{
		if (cont->outfile_type[i] == 1)
			fd_outfile[i] = open(cont->outfile[i], O_CREAT | O_WRONLY, 0644);
		else if (cont->outfile_type[i] == 2)
			fd_outfile[i] = open(cont->outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		fd->outfile = fd_outfile[i];
		if (fd_outfile[i] == -1)
			return (perror(cont->outfile[i]), 1);
	}
	return (0);
}

void	ft_execute_one_cmd(t_cont *cont, t_env *env)
{
	t_execve	exec;	
	t_fd		fd;
	pid_t		id;

	ft_open_files(cont, &fd);
	id = fork();
	ft_syscall(id, "fork");
	if (id == 0)
	{
		if (dup2(fd.infile, STDIN_FILENO) == -1)
			(perror("dup2 (in_fd)"), exit(EXIT_FAILURE));
		if (fd.infile != 0)
			close(fd.infile);
		if (dup2(fd.outfile, STDOUT_FILENO) == -1)
			(perror("dup2 (out_fd)"), exit(EXIT_FAILURE));
		if (fd.outfile != 1)
			close(fd.outfile);
		if (ft_check_commands(cont, env) == 1)
			(ft_free_containers(&cont), ft_free_env(&env), exit(SUCCESS));
		ft_check_(&exec.cmd_path, cont->cmd, env);
		exec.argv = ft_join_for_argv_execve(cont);
		exec.envp = ft_join_for_envp_execve(env);
		if (execve(exec.cmd_path, exec.argv, exec.envp) == -1)
			(ft_f(exec.argv), ft_f(exec.envp), perror("execve"), exit(FAIL));
	}
	wait(CHILD);
}

void	ft_free_tmp(t_tmp_cont **tmp)
{
	int	i;

	i = 0;
	free((*tmp)->cmd);
	while ((*tmp)->arg[i] != NULL)
		(1) && (free((*tmp)->arg[i]), i++);
	free((*tmp)->arg);
	i = 0;
	while ((*tmp)->inf[i] != NULL)
		(1) && (free((*tmp)->inf[i]), i++);
	free((*tmp)->inf);
	i = 0;
	while ((*tmp)->outf[i] != NULL)
		(1) && (free((*tmp)->outf[i]), i++);
	free((*tmp)->outf);
	free((*tmp)->out_t);
	free(*tmp);
}

void	ft_count_alc(t_token *head, t_tmp_cont	**cont)
{
	t_token	*temp;
	t_count	c;

	(1) && (temp = head, (*cont) = malloc(sizeof(t_tmp_cont)));
	ft_check_allocation((*cont));
	(1) && (c.arg = 0, c.infile = 0, c.outfile = 0);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == ARG)
			c.arg++;
		else if (temp->type == INFILE)
			c.infile++;
		else if (temp->type == OUTFILE || temp->type == APPEND)
			c.outfile++;
		temp = temp->next;
	}
	(*cont)->arg = malloc((c.arg + 1) * sizeof(char *));
	ft_check_allocation((*cont)->arg);
	(*cont)->inf = malloc((c.infile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->inf);
	(*cont)->outf = malloc((c.outfile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->outf);
	(*cont)->out_t = malloc((c.outfile + 1) * sizeof(int));
	ft_check_allocation((*cont)->out_t);
}

//	create a function that create a node that holds what inside the t_cont
void ft_link_all_in_containers(t_token *head, t_cont **container)
{
	t_tmp_cont	*t;
	t_cc		c;

	(1) && (*container = NULL);
	while (head != NULL)
	{
		((1) && (c.i = 0, c.j = 0, c.z = 0, c.y = 0), ft_count_alc(head, &t));
		while (head != NULL && head->type != PIPE)
		{
			if (head->type == CMD)
				t->cmd = ft_strdup(head->token);
			else if (head->type == ARG)
				t->arg[c.i++] = ft_strdup(head->token);
			else if (head->type == INFILE)
				t->inf[c.j++] = ft_strdup(head->next->token);
			else if (head->type == OUTFILE || head->type == APPEND)
			{
				t->outf[c.y] = ft_strdup(head->next->token);
				if (head->type == OUTFILE)
					t->out_t[c.y] = 1;
				if (head->type == APPEND)
					t->out_t[c.y] = 2;
				c.y++;
			}
			head = head->next;
		}
		(1) && (t->arg[c.i] = 0, t->inf[c.j] = 0, t->outf[c.y] = 0, t->out_t[c.y] = 0);
		(ft_push_container(t, container), ft_free_tmp(&t));
		if (head != NULL && head->type == PIPE)
			head = head->next;
	}
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
	if (nbr_cmd == 1)
		ft_execute_one_cmd(container, env);
	ft_free_containers(&container);
}
