/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 10:13:27 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_current_pwd(t_env *envp, char *argument)
{
	t_env	*head;
	int		flag;
	char	*tmp;

	head = envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			head->value = ft_strjoin("PWD=", argument);
			if (!head->value)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			flag = 1;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		tmp = ft_strjoin("PWD=", argument);
		if (!tmp)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		if (ft_push_value(tmp, &envp) == 0)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
}

static void	ft_add_old_pwd(t_env *envp, char *argument)
{
	t_env	*head;
	int		flag;
	char	*tmp;

	head = envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "OLDPWD=", 4) == 0)
		{
			head->value = ft_strjoin("OLDPWD=", argument);
			if (!head->value)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			flag = 1;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		tmp = ft_strjoin("OLDPWD=", argument);
		if (!tmp)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		if (ft_push_value(tmp, &envp) == 0)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
}

static int	ft_check_argument(char **argument)
{
	if (getenv("HOME") == NULL && *argument == NULL)
		return (write(2, "cd: HOME not set\n", 17), 1);
	if ((*argument) == NULL || (*argument)[0] == '\0'
		|| ft_strncmp(*argument, "--", ft_strlen(*argument)) == 0)
	{
		*argument = ft_strdup(getenv("HOME"));
		if (!*argument)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	if ((*argument)[0] == '~')
	{
		if ((*argument)[1] == '/' || (*argument)[1] == '\0')
		{
			free(*argument);
			*argument = ft_strjoin(getenv("HOME"), (*argument) + 1);
			if (!(*argument))
				return (1);
		}
		else
			return (write(2, "syntax not supported\n", 21), 1);
	}
	return (0);
}

int	ft_cd(char *argument, t_env *envp)
{
	char		current_dir[PATH_MAX];
	char		buf[PATH_MAX];
	static char	last_dir[PATH_MAX];
	t_env		*head;

	if (last_dir[0] == '\0')
		return (write(2, "cd: OLDPWD not set\n", 19), 1);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		*current_dir = '\0';
	if (ft_check_argument(&argument) == 1)
		return (1);
	if (chdir(argument) == -1)
		return (perror(argument), 1);
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		write(2, "syntax not supported\n", 21);
	ft_add_current_pwd(envp, buf);
	ft_strlcpy(last_dir, current_dir, ft_strlen(current_dir));
	ft_add_old_pwd(envp, last_dir);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_env	*envp;
// 	t_env	*head;

// 	envp = ft_check_env(env);
// 	head = envp;
// 	while (head)
// 	{
// 		printf("%s\n", head->value);
// 		head = head->next;
// 	}
// 	head = envp;
// 	printf(YELLOW"=======Before=======\n"RESET);
// 	while (head != NULL)
// 	{
// 		if (ft_strncmp(head->value, "PWD", 3) == 0)
// 			printf("%s\n", head->value);
// 		if (ft_strncmp(head->value, "OLDPWD", 6) == 0)
// 			printf("%s\n", head->value);
// 		head = head->next;
// 	}
// 	ft_cd(av[1], envp);
// 	head = envp;
// 	printf(YELLOW"\n\n=======After=======\n"RESET);
// 	while (head != NULL)
// 	{
// 		if (ft_strncmp(head->value, "PWD", 3) == 0)
// 			printf("%s\n", head->value);
// 		if (ft_strncmp(head->value, "OLDPWD", 6) == 0)
// 			printf("%s\n", head->value);
// 		head = head->next;
// 	}
// }
