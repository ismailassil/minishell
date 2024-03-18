/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 02:36:47 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cont	*new_cmd()
{
	t_cont	*seg_cmd;
	int		i;

	seg_cmd = malloc(sizeof(t_cont));
	if (!seg_cmd)
		return (NULL);
	seg_cmd->cmd = NULL;
	seg_cmd->arg = malloc(sizeof(char *) * (MAX + 1));
	i = 0;
	while (i < (MAX + 1))
	{
		seg_cmd->arg[i] = NULL;
		i++;
	}
	seg_cmd->infile = malloc(sizeof(char *) * (MAX + 1));
	i = 0;
	while (i < (MAX + 1))
	{
		seg_cmd->infile[i] = NULL;
		i++;
	}
	seg_cmd->outfile = malloc(sizeof(char *) * (MAX + 1));
	i = 0;
	while (i < (MAX + 1))
	{
		seg_cmd->outfile[i] = NULL;
		i++;
	}
	seg_cmd->append = malloc(sizeof(char *) * (MAX + 1));
	i = 0;
	while (i < (MAX + 1))
	{
		seg_cmd->append[i] = NULL;
		i++;
	}
	seg_cmd->in = 0;
	seg_cmd->out = 1;
	seg_cmd->opened_fd = NULL;
	seg_cmd->next = NULL;
	return (seg_cmd);
}

t_cont	*last_cmd(t_cont	*seg_cmd)
{
	while (seg_cmd && seg_cmd->next)
	{
		seg_cmd = seg_cmd->next;
	}
	return (seg_cmd);
}

t_cont	*push_cmd(t_cont	**cmds)
{
	t_cont	*seg_cmd;

	seg_cmd = new_cmd();
	if (!seg_cmd)
		return (NULL);
	if (!last_cmd(*cmds))
		*cmds = seg_cmd;
	else
		last_cmd(*cmds)->next = seg_cmd;
	return (last_cmd(*cmds));
}

int	count_pipe(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->token[0] == '|')
			i++;
		head = head->next;
	}
	return (i);
}


t_tree	*create_node_tree(t_cont *cmd_node)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->cont = cmd_node;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_cont	*find_prev_node(t_cont *token, t_cont *current)
{
	while (token && token->next != current)
	{
		token = token->next;
	}
	return (token);
}

//////////------------------------------Buil_tree---------------------------///////////////
t_tree	*build_tree(t_cont *token, t_cont *head)
{
	t_tree	*treer;
	t_cont	*hd;
	t_cont	*fn;

	treer = NULL;
	fn = NULL;
	hd = token;
	if (!token)
		return (NULL);
	while (hd)
	{
		if (hd->cmd && hd->cmd[0] == '|')
		{
			fn = hd;
			break ;
		}
		hd = hd->next;
	}
	if (!fn)
		return (create_node_tree(token));
	else
	{
		t_cont *lef;
		treer = create_node_tree(fn);
		if (!treer)
			return (NULL);
		treer->right = build_tree(fn->next, head);
		lef = find_prev_node(head, fn);
		if (lef)
		{
			// printf("\ncmd %s\n", lef->cmd);
			lef->next = NULL;
		}
		treer->left = build_tree(lef, head);
	}
	return (treer);
}
//////////------------------------------Buil_tree---------------------------///////////////

void treeprint(t_tree *root, int level)
{
	if (root == NULL)
			return;
	for (int i = 0; i < level; i++)
			printf(i == level - 1 ? "<-" : "  ");
	printf("%s\n", root->cont->cmd);
	treeprint(root->left, level + 1);
	treeprint(root->right, level + 1);
}

char	*append_char_front(char *file_name, char c)
{
	int		i;
	int		len;
	char	*res;

	len = (int)ft_strlen(file_name);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	res[0] = c;
	i = 0;
	while (file_name && file_name[i])
	{
		res[i + 1] = file_name[i];
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}

char	*mingle_path(char *path, char *file)
{
	char	*file_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	file_path = malloc(sizeof(char) * ((int)ft_strlen(path) + (int)ft_strlen(file) + 1));
	if (!file_path)
		return (NULL);
	while (path && path[i])
	{
		file_path[i] = path[i];
		i++;
	}
	while (file && file[j])
	{
		file_path[i + j] = file[j];
		j++;
	}
	file_path[i + j] = '\0';
	return (file_path);
}
/**
 * it must change out for left
 * it must change in for right
 * 
*/

void	set_open_fd(t_opened_fd *opened_fd, int fd1, int fd2, int fn)
{
	static int	i;

	if (fn == 1)
	{
		while (i >= 0)
			close(opened_fd->fd[i--]);
		i = 0;
	}
	else
	{
		opened_fd->fd[i++] = fd1;
		opened_fd->fd[i++] = fd2;
	}
}

int	open_and_return_inf(char **infile)
{
	int	i;
	int	fd_in;

	i = 0;
	fd_in = 0;
	while(infile[i])
	{
		fd_in = open(infile[i++], O_RDONLY);
		if (fd_in == -1)
			(ft_printf("msh: %s No such file or directory\n", infile[i - 1]), exit(1));
	}
	return (fd_in);
}

int	open_and_return_ouf(char **outfile)
{
	int	i;
	int	fd_out;

	fd_out = 0;
	i = 0;
	while(outfile[i])
		fd_out = open(outfile[i++], O_CREAT | O_RDWR, 0777);
	return (fd_out);
}

void	close_opened_fds(t_tree *root)
{
	int	i;

	i = 0;
	while(root->cont->opened_fd && root->cont->opened_fd->fd[i] != 0)
		close(root->cont->opened_fd->fd[i++]);
}

void	execute_within_child(t_tree *root, char **e, char *full_path)
{
	int fd_in = 0;
	int fd_out = 0;

	if (root->cont->infile)
		(fd_in = open_and_return_inf(root->cont->infile));
	if (fd_in)
		dup2(fd_in, 0);
	else
		dup2(root->cont->in, 0);
	if (root->cont->outfile)
		fd_out = open_and_return_ouf(root->cont->outfile);	
	if (fd_out)
		dup2(fd_out, 1);
	else
		dup2(root->cont->out, 1);
	close_opened_fds(root);
	if (execve(full_path, root->cont->arg, e) == -1)
		(ft_printf("msh: command not found: %s\n",root->cont->arg[0]), exit(1));
}

char	*scrap_full_path(t_tree *root, char **path)
{
	char	*cmd_name;
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	cmd_name = append_char_front(root->cont->cmd, '/');
	while (path[i])
	{
		full_path = mingle_path(path[i], cmd_name);
		if (!access(root->cont->cmd, F_OK | X_OK))
			(free(full_path), full_path = root->cont->cmd);
		if (access(full_path, F_OK | X_OK) != -1)
			break ;
		free(full_path);
		i++;
	}
	return (full_path);
}

void	assign_left_leaf(int *fd, t_opened_fd *opened_fd, t_tree *root)
{
	root->left->cont->opened_fd = opened_fd;
	root->left->cont->out = fd[1];
	root->left->cont->in = root->cont->in;
}

void	assign_right_leaf(int *fd, t_opened_fd *opened_fd, t_tree *root)
{
	root->right->cont->opened_fd = opened_fd;
	root->right->cont->in = fd[0];
}

void	traverse_tree_exec(t_tree *root, char **path, char **e, t_opened_fd *opened_fd)
{
	pid_t	pid;
	int		fd[2];
	char	*full_path;

	if (root)
	{
		if (root->cont->cmd && root->cont->cmd[0] == '|')
		{
			pipe(fd);
			set_open_fd(opened_fd, fd[0], fd[1], 0);
			if 	(root->left)
			{
				assign_left_leaf(fd, opened_fd, root);
				traverse_tree_exec(root->left, path, e, opened_fd);
			}
			if (root->right)
			{
				assign_right_leaf(fd, opened_fd, root);
				traverse_tree_exec(root->right, path, e, opened_fd);
			}
			(close(fd[0]), close(fd[1]));
		}
		else
		{
			full_path = scrap_full_path(root, path);
			pid = fork();
			if (pid == 0)
				execute_within_child(root, e, full_path);
		}
	}
}

t_cont	*handle_execution(t_token	*head, t_env *env, char **e)
{
	t_cont	*seg_cmd;
	t_cont	*current_cmd;
	int		i;
	int		count_p;
	int		out;
	int		in;
	int		ar;
	(void)env;

	i = 0;
	count_p = count_pipe(head);
	seg_cmd = NULL;

	while (i <= count_p)
	{
		current_cmd = push_cmd(&seg_cmd);
		out = 0;
		in = 0;
		ar = 0;
		while (head && current_cmd)
		{
			if (head->token[0] == '|')
			{
				//-----------only-suits-for-tree----------------//
				current_cmd = push_cmd(&seg_cmd);
				current_cmd->cmd = head->token;
				//----------------------------------------------//
				head = head->next;
				break ;
			}
			if (head->type == CMD)
			{
				current_cmd->cmd = head->token;
				current_cmd->arg[ar++] = head->token;
			}
			else if (head->type == ARG)
			{
				current_cmd->arg[ar++] = head->token;
			}
			else if (head->type == INFILE)
			{
				current_cmd->infile[in++] = head->next->token;
			}
			else if (head->type == OUTFILE)
			{
				current_cmd->outfile[out++] = head->next->token;
			}
			head = head->next;
		}
		i++;
	}
	/////////----------------------------execution---------------------------------/////////////////
	// i = 0;
	// int original_stdin_fd = dup(STDIN_FILENO);

	// pipe(fd);
	// while (i <= count_p)
	// {
	// 	pid = fork();
	// 	if (pid < 0)
	// 		perror("Error\n");
	// 	else if (pid == 0)
	// 	{
	// 		close(fd[0]);
	// 		////////////single-------command///////////
	// 		if (i == 0 && count_p == 0)
	// 		{
	// 			close(fd[1]);
	// 			execve("/usr/bin/clear", seg_cmd->arg, env);
	// 		}
	// 		else if (i == 0)
	// 		{
	// 			dup2(fd[1], STDOUT_FILENO);
	// 			close(fd[1]);
	// 			execve("/bin/ls", seg_cmd->arg, env);
	// 		}
	// 		else
	// 		{
	// 			close(fd[1]);
	// 			execve("/usr/bin/grep", seg_cmd->arg, env);
	// 		}
	// 	}
	// 	else if (pid != 0)
	// 	{
	// 		close(fd[1]); // Close write end of the pipe in the parent process
    //         if (i != count_p) {
    //             dup2(fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
    //             close(fd[0]); // Close the read end of the pipe
    //         }
	// 		seg_cmd = seg_cmd->next;
	// 	}
	// 	i++;
	// }
	// dup2(original_stdin_fd, STDIN_FILENO);
	// close(original_stdin_fd);
	// close(fd[0]);
	// while (wait(NULL) != -1)
	// 	;
	/////////----------------------------------------------------------------------/////////////////

	// while (seg_cmd)
	// {
		
	// 	i = 0;
	// 	printf("\n-----------------------------------------------\n");
	// 	printf("\ncmd    %s \n", seg_cmd->cmd);
	// 	while (seg_cmd->arg && seg_cmd->arg[i] && i < 2)
	// 		printf("arg     %s\n", seg_cmd->arg[i++]);
	// 	i = 0;
	// 	while (seg_cmd->infile && seg_cmd->infile[i] && i < 2)
	// 		printf("infile     %s\n", seg_cmd->infile[i++]);
	// 	i = 0;
	// 	while (seg_cmd->outfile && seg_cmd->outfile[i] && i < 2)
	// 		printf("outfile     %s\n", seg_cmd->outfile[i++]);
	// 	printf("-----------------------------------------------\n");
	// 	seg_cmd = seg_cmd->next;
	// }
	// exit(1);
	////////////////////////////////////////////////////////////////////////////////////////
	t_tree *tt;
	char **en = handle_paths(env);
	t_opened_fd *opened_fd = malloc(sizeof(t_opened_fd));
	set_open_fd(opened_fd, 0, 0, 1);
	i = 0;
	while (i < MAX)
	{
		opened_fd->fd[i++] = 0;
	}
	// printf("build _ tree\n");
	tt = build_tree(seg_cmd, seg_cmd);
	// treeprint(tt, 0);
	
	traverse_tree_exec(tt, en, e, opened_fd);
	while (wait(NULL) != -1)
		;
	////////////////////////////////////////////////////////////////////////////////////////
	// dup2(original_stdin_fd, STDIN_FILENO);
	// close(original_stdin_fd);
	// close(fd[0]);
	// if (tt)
	// {
	// 	if (tt->left)
	// 		printf("left    = %s\n", tt->left->cont->cmd);
	// 	if (tt->right)
	// 		printf("right    = %s\n", tt->right->cont->cmd);
	// 	if (tt->right->right)
	// 		printf("right->right    = %s\n", tt->right->right->cont->cmd);
	// 	if (tt->right->left)
	// 		printf("right->left    = %s\n", tt->right->left->cont->cmd);
	// }
	return (seg_cmd);
}

/*	handle ctr+c & ctrl+\	*/
void	handle_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(t_env *env, char *input, char **en)
{
	char	*shell;
	t_token	*head;
	(void)en;
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

	////////////////////////////
	handle_execution(head, env, en);
	////////////////////////////

	// ft_execution(&head);
}

void	v(void)
{
	system("lsof -c minishell");
}


int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*envp;

	atexit(v);
	// ft_signal_handler();

	// ft_printf("hello wolrd");
	// exit(0);
	////------signals---------//////////
	signal(SIGINT, handle_c);
	signal(SIGQUIT, handle_c);
	rl_catch_signals = 0;
	////------signals---------//////////

	((void)argc, (void)argv);
	envp = NULL;
	envp = ft_get_env(env);
	while (true)
	{
		line = readline(YELLOW_"minishell$ "RESET);
		if (line == NULL)
		{
		
			printf("exit\n");
			ft_exit();
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parse_input_from_shell(envp, line, env);
		free(line);
		printf("\n");
	}
}
