/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 19:09:12 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>

/*	Checks if there is any space char	*/
bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

/*	Checks if there is any special char	*/
bool	ft_special_char(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\'' || c == '\"')
		return (true);
	return (false);
}

/*	Print the data in the Linked list imported from the shell	*/
void	ft_print(t_container *lst)
{
	t_container	*head = lst;

	while (head != NULL)
	{
		printf("====={%s}=====\n", head->holder);
		head = head->next;
	}
}

/*	Add the input from shell to linked list	*/
void	ft_add_holder_to_container(t_container	**spart, char *input, int i, int index)
{
	char		*tmp;
	t_container	*holder;

	tmp = ft_substr(input, i - index, index);
	holder = ft_lstnew(tmp);
	if (holder == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(spart, holder);
	// printf("===={%s}====\n", holder->holder);
}

/*	Parse the input from the shell	*/
void	ft_parse_input_from_shell(char *input)
{
	int			i;
	int			index;
	t_container	*spart;

	spart = NULL;
	(1) && (i = 0, index = 0);
	while (input[i] != '\0')
	{
		while (ft_isspace(input[i]) == true && input[i] != '\0')
			i++;
		while (ft_isspace(input[i]) == false && ft_special_char(input[i]) == false && input[i] != '\0')
			(index++, i++);
		ft_add_holder_to_container(&spart, input, i, index);
	}
	ft_print(spart);
}

bool	ft_find_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'i' && line[i + 3] == 't')
			return (true);
		i++;
	}
	return (false);
}

void	ft_check_env(t_env **envp, char **env)
{
	char	pwd[PATH_MAX];
	char	*name;
	char	*value;

	if (env != NULL)
	{
		printf("NO ENV\n");
		*envp = NULL;
	}
	else
	{
		getcwd(pwd, sizeof(pwd));
		name = ft_strdup("PATH");
		value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
		ft_lstadd_back_env(envp, ft_lstnew_env(name, value));
		name = ft_strdup("PWD");
		value = ft_strdup(pwd);
		ft_lstadd_back_env(envp, ft_lstnew_env(name, value));
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	**envp;

	((void)argc, (void)argv, (void)env);
	ft_signal_handler();
	ft_check_env(envp, env);
	while (true)
	{
		line = readline(YELLOW"minishell$ "RESET);
		if (line == NULL || ft_find_exit(line) == true)
			ft_exit();
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parse_input_from_shell(line);
		free(line);
	}
}
