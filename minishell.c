/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/15 02:52:51 by aibn-che         ###   ########.fr       */
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

void	traverse_tree_exec(t_tree *root, t_tree* parent)
{
	pid_t	pid;
	int		fd[2];
	// int 	fd_child[2];

	if (root)
	{
		if (root->cont->cmd[0] == '|')
		{
			if 	(root->left)
			{
				traverse_tree_exec(root->left, root);
			}
			if (root->right)
			{
				traverse_tree_exec(root->right, root);
			}
		}
		else
		{
			if (root->cont->arg[0][0] == 'l')
			{
				printf("dddddddd\n");
				pipe(fd);
				pid = fork();
				if (pid == 0)
				{
					close(fd[0]);
					if (parent->right)
						dup2(fd[1], 1);
					close(fd[1]);
					execve("/bin/ls", root->cont->arg, NULL);
				}
				else
					close(fd[1]);
			}
			else
			{
				// pipe(fd_child);
				pid = fork();
				if (pid == 0)
				{
					// close(fd_child[0]);
					// close(fd_child[1]);
					close(fd[1]);
					dup2(fd[0], 0);
					close(fd[0]);
					if (root->cont->arg[0][0] == 'g')
						execve("/usr/bin/grep", root->cont->arg, NULL);
					if (root->cont->arg[0][0] == 'w')
						execve("/usr/bin/wc", root->cont->arg, NULL);
				}
				else
				{
					// close(fd_child[0]);
					// close(fd_child[1]);
					// close(fd[0]);
					close(fd[1]);
				}
			}
			while (wait(NULL) != -1)
				;
		}
	}
}

int	count_nodes(t_tree *root, int i)
{
	if (root && root->cont->cmd[0] != '|')
	{
		printf("\ncount %s  len = %zu\n", root->cont->cmd, ft_strlen(root->cont->cmd));
		i+=1;
	}
	if (root->left)
	{
		printf("\n root =  %s  left", root->cont->cmd);
		i += count_nodes(root->left, i);
	}
	if (root->right)
	{
		printf("\n root =  %s  right", root->cont->cmd);
		i += count_nodes(root->right, i);
	}
	return (i);
}

t_cont	*handle_execution(t_token	*head, char **env)
{
	t_cont	*seg_cmd;
	t_cont	*current_cmd;
	int		i;
	int		count_p;
	int		out;
	int		in;
	int		ar;
	(void)env;
	// pid_t	pid;
	// int		fd[2];

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
	// 	printf("\ncmd    %s \n", seg_cmd->cmd);
	// 	while (seg_cmd->arg && seg_cmd->arg[i] && i < 2)
	// 		printf("arg     %s\n", seg_cmd->arg[i++]);
	// 	i = 0;
	// 	while (seg_cmd->infile && seg_cmd->infile[i] && i < 2)
	// 		printf("infile     %s\n", seg_cmd->infile[i++]);
	// 	i = 0;
	// 	while (seg_cmd->outfile && seg_cmd->outfile[i] && i < 2)
	// 		printf("outfile     %s\n", seg_cmd->outfile[i++]);
	// 	seg_cmd = seg_cmd->next;
	// }
	t_tree *tt;

	// printf("leaf count = %d\n",count_nodes(tt, 0));
	tt = build_tree(seg_cmd, seg_cmd);
	traverse_tree_exec(tt, tt);
	// count_nodes(tt);
	// dup2(original_stdin_fd, STDIN_FILENO);
	// close(original_stdin_fd);
	// close(fd[0]);
	// treeprint(tt, 0);
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
	handle_execution(head, en);
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
