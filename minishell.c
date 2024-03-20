/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 03:06:24 by aibn-che         ###   ########.fr       */
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
	seg_cmd->infile = malloc(sizeof(char *) * (MAX + 1));
	seg_cmd->outfile = malloc(sizeof(char *) * (MAX + 1));
	seg_cmd->append = malloc(sizeof(char *) * (MAX + 1));
	seg_cmd->her_doc = malloc(sizeof(char *) * (MAX + 1));
	i = 0;
	while (i < (MAX + 1))
	{
		seg_cmd->arg[i] = NULL;
		seg_cmd->infile[i] = NULL;
		seg_cmd->outfile[i] = NULL;
		seg_cmd->append[i] = NULL;
		seg_cmd->her_doc[i] = NULL;
		i++;
	}
	seg_cmd->in = 0;
	seg_cmd->out = 1;
	seg_cmd->out_app = 0;
	seg_cmd->in_app = 0;
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

int	handle_herdoc(t_tree *root)
{
	int		i;
	char	*str;
	int		fd[2];

	i = 0;
	if (root->cont->her_doc)
	{
		while (root->cont->her_doc[i] && root->cont->her_doc[i + 1])
		{
			write(1, "> ", 2);
			str = get_next_line(0);
			while (str)
			{
				if (!ft_strncmp(str, root->cont->her_doc[i], ft_strlen(str) - 1) && root->cont->her_doc[i][ft_strlen(str) - 1] == '\0')
					break ;
				write(1, "> ", 2);
				str = get_next_line(0);
			}
			i++;
		}
		while (root->cont->her_doc[i])
		{
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
			write(1, "> ", 2);
			str = get_next_line(0);
			while (str)
			{
				if (!ft_strncmp(str, root->cont->her_doc[i], ft_strlen(str) - 1) && root->cont->her_doc[i][ft_strlen(str) - 1] == '\0')
					break ;
				write(fd[1], str, ft_strlen(str));
				write(1, "> ", 2);
				str = get_next_line(0);
			}
			i++;
			close(fd[1]);
		}
	}
	return (fd[0]);
}

int	open_and_return_inf(t_tree *root)
{
	int	i;
	int	fd_in;

	i = 0;
	fd_in = 0;
	if (root->cont->in_app)
	{
		while(root->cont->infile[i])
		{
			fd_in = open(root->cont->infile[i++], O_RDONLY);
			if (fd_in == -1)
				(ft_printf("msh: %s No such file or directory\n", root->cont->infile[i - 1]), exit(1));
		}
		fd_in = handle_herdoc(root);
		return (fd_in);
	}
	else
	{
		handle_herdoc(root);
		while(root->cont->infile[i])
		{
			fd_in = open(root->cont->infile[i++], O_RDONLY);
			if (fd_in == -1)
				(ft_printf("msh: %s No such file or directory\n", root->cont->infile[i - 1]), exit(1));
		}
	}
	return (fd_in);	
}

int	open_and_return_ouf(t_cont *cont)
{
	int	i;
	int	fd_out;

	fd_out = 0;
	i = 0;
	if (cont->out_app)
	{
		while(cont->outfile[i])
			open(cont->outfile[i++], O_CREAT | O_RDWR | O_TRUNC, 0777);
		i = 0;
		while (cont->append[i])
			fd_out = open(cont->append[i++], O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	else
	{
		while (cont->append[i])
			open(cont->append[i++], O_CREAT | O_RDWR | O_APPEND, 0777);
		i = 0;
		while(cont->outfile[i])
			fd_out = open(cont->outfile[i++], O_CREAT | O_RDWR | O_TRUNC, 0777);
	}
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

	////////////////////infile//////////////////////////
	if (root->cont->infile || root->cont->her_doc)
		(fd_in = open_and_return_inf(root));
	if (fd_in)
		dup2(fd_in, 0);
	else
		dup2(root->cont->in, 0);
	////////////////////infile//////////////////////////
	////////////////////outfile//////////////////////////
	if (root->cont->outfile || root->cont->append)
		fd_out = open_and_return_ouf(root->cont);	
	if (fd_out)
		dup2(fd_out, 1);
	else
		dup2(root->cont->out, 1);
	// fprintf(stderr,"outfile %d\n", root->cont->out);
	////////////////////outfile//////////////////////////
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

t_cont	*accumulate_cmds_with_their_params(t_token *head)
{
	int		count_p;
	int		out;
	int		app;
	int		in;
	int		ar;
	int		her;
	int		i;
	t_cont	*current_cmd;
	t_cont	*head_cmd;

	count_p = count_pipe(head);
	head_cmd = NULL;
	i = 0;
	while (i <= count_p)
	{
		current_cmd = push_cmd(&head_cmd);
		(1) && (out = 0, in = 0, ar = 0, app = 0, her = 0);
		while (head && current_cmd)
		{
			if (head->token[0] == '|')
			{
				current_cmd = push_cmd(&head_cmd);
				(current_cmd->cmd = head->token, head = head->next);
				break ;
			}
			if (head->type == CMD)
			{
				current_cmd->cmd = head->token;
				current_cmd->arg[ar++] = head->token;
			}
			else if (head->type == ARG)
				current_cmd->arg[ar++] = head->token;
			else if (head->type == INFILE)
			{
				current_cmd->in_app = 0;
				current_cmd->infile[in++] = head->next->token;
			}
			else if (head->type == OUTFILE)
			{
				current_cmd->out_app = 0;
				current_cmd->outfile[out++] = head->next->token;
			}
			else if (head->type == APPEND)
			{
				current_cmd->out_app = 1;
				current_cmd->append[app++] = head->next->token;
			}
			else if (head->type == HEREDOC)
			{
				current_cmd->in_app = 1;
				current_cmd->her_doc[her++] = head->next->token;
			}
			head = head->next;
		}
		i++;
	}
	return (head_cmd);
}

t_cont	*handle_execution(t_token *head, t_env *env, char **e)
{
	t_cont		*head_cmd;
	t_tree		*b_treee;
	t_opened_fd	*opened_fd;
	int			i;
	char		**en;

	i = 0;
	head_cmd = accumulate_cmds_with_their_params(head);
	en = handle_paths(env);
	opened_fd = malloc(sizeof(t_opened_fd));
	set_open_fd(opened_fd, 0, 0, 1);
	while (i < MAX)
	{
		opened_fd->fd[i++] = 0;
	}
	b_treee = build_tree(head_cmd, head_cmd);
	// handle_herdoc(b_treee, 1);
	// exit(1);
	traverse_tree_exec(b_treee, en, e, opened_fd);
	while (wait(NULL) != -1)
		;
	return (head_cmd);
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