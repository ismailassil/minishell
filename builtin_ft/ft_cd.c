/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/03/19 18:11:05 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_if_not_found(t_env **envp, int flag, char *arg, char *string)
{
	char	*tmp;

	if (flag == 0)
	{
		tmp = ft_strjoin(string, arg);
		if (!tmp)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		if (ft_push_value(tmp, envp) == 0)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		(1) && (free(tmp), tmp = NULL);
	}
}

static char	*ft_check_argument(char *argument)
{
	char	*arg;

	arg = ft_strdup(argument);
	if (getenv("HOME") == NULL && argument == NULL)
		return (write(2, "msh: cd: HOME not set\n", 22), NULL);
	else if (argument == NULL || argument[0] == '\0')
	{
		arg = ft_strdup(getenv("HOME"));
		if (!arg)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	else if (argument[0] == '~' || argument[0] == '-')
		return (write(2, "msh: syntax not supported\n", 26), NULL);
	return (arg);
}

static void	ft_add_current_pwd(t_env **envp, char *argument)
{
	t_env	*head;
	int		flag;
	char	*tmp;

	head = *envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			(1) && (free(head->value), head->value = NULL);
			tmp = ft_strjoin("PWD=", argument);
			if (!tmp)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			head->value = tmp;
			flag = 1;
			break ;
		}
		head = head->next;
	}
	ft_add_if_not_found(envp, flag, argument, "PWD=");
}

static void	ft_add_old_pwd(t_env **envp, char *argument)
{
	t_env	*head;
	int		flag;
	char	*tmp;

	head = *envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "OLDPWD=", 4) == 0)
		{
			(1) && (free(head->value), head->value = NULL);
			tmp = ft_strjoin("OLDPWD=", argument);
			if (!tmp)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			head->value = tmp;
			flag = 1;
			break ;
		}
		head = head->next;
	}
	ft_add_if_not_found(envp, flag, argument, "OLDPWD=");
}

int	ft_cd(char *argument, t_env **envp)
{
	char		current_dir[PATH_MAX];
	char		buf[PATH_MAX];
	char		*dir;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		*current_dir = '\0';
	dir = ft_check_argument(argument);
	if (dir == NULL)
		return (1);
	if (chdir(dir) == -1)
		return ((*envp)->status = 1, free(dir), 1);
	if (getcwd(buf, sizeof(buf)) != NULL)
		(*envp)->status = 0;
	else
		(1) && (ft_error( "msh: syntax not supported\n"), (*envp)->status = 258);
	(ft_add_current_pwd(envp, buf), ft_add_old_pwd(envp, current_dir));
	free(dir);
	return (0);
}

// void	v(void)
// {
// 	system("leaks cd");
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_env	*envp;
// 	t_env	*head;
// 	atexit(v);

// 	envp = ft_get_env(env);
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
// 	ft_cd(av[1], &envp);
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
// 	ft_free_env(&envp);
// }
