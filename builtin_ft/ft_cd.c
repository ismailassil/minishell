/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 17:07:00 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_tilda_and_minus(char *argument, char *last_dir)
{
	char	*arg;

	arg = NULL;
	if (argument[0] == '-' && argument[1] == '\0')
	{
		if (last_dir == NULL)
			return (write(2, "cd: OLDPWD not set\n", 19), NULL);
		arg = ft_strdup(last_dir);
		if (!arg)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	else if (argument[0] == '~')
	{
		if (argument[1] == '/' || argument[1] == '\0')
		{
			arg = ft_strjoin(getenv("HOME"), argument + 1);
			if (!arg)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		}
		else
			return (write(2, "syntax not supported\n", 21), NULL);
	}
	return (arg);
}

static char	*ft_check_argument(char *argument, char *last_dir)
{
	char	*arg;

	arg = NULL;
	if (getenv("HOME") == NULL && argument == NULL)
		return (write(2, "cd: HOME not set\n", 17), NULL);
	else if (argument == NULL)
	{
		arg = ft_strdup(getenv("HOME"));
		if (!arg)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	else if (argument[0] == '\0'
		|| (argument[0] == '-' && argument[1] == '-' && argument[2] == '\0'))
	{
		arg = ft_strdup(getenv("HOME"));
		if (!arg)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	else
		arg = ft_check_tilda_and_minus(argument, last_dir);
	if (!arg)
		return (NULL);
	return (arg);
}

static char	*ft_extract_old_pwd(t_env *envp)
{
	t_env	*head;
	int		flag;
	char	*last_dir;

	head = envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "OLDPWD=", 7) == 0)
		{
			flag = 1;
			last_dir = ft_substr(head->value, 7, ft_strlen(head->value) - 7);
			if (last_dir == NULL)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			return (last_dir);
		}
		head = head->next;
	}
	if (flag == 0)
		return (NULL);
	return (NULL);
}

int	ft_cd(char *argument, t_env **envp)
{
	char		current_dir[PATH_MAX];
	char		buf[PATH_MAX];
	char		*last_dir;
	char		*dir;

	last_dir = ft_extract_old_pwd(*envp);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		*current_dir = '\0';
	dir = ft_check_argument(argument, last_dir);
	if (dir == NULL)
		return (free(last_dir), 1);
	if (chdir(dir) == -1)
		return (free(last_dir), free(dir), perror(argument), 1);
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		write(2, "syntax not supported\n", 21);
	(ft_add_current_pwd(envp, buf), ft_add_old_pwd(envp, current_dir));
	free(dir);
	if (last_dir)
		free(last_dir);
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
