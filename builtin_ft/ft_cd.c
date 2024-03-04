/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/03/04 20:16:08 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_old_pwd(t_env *envp, char *argument)
{
	t_env	*head;
	int		flag;

	head = envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "OLDPWD=", 7) == 0)
		{
			head->value = ft_strjoin("OLDPWD=", argument);
			if (!head->value)
				(write(2, "Error: Allocation failed\n", 25), exit(EXIT_FAILURE));
			flag = 1;
		}
		head = head->next;
	}
	if (flag == 0)
		(printf("HERE\n"), ft_push_value(ft_strjoin("OLDPWD=", argument), &envp));
}

static int	ft_check_argument(char **argument)
{
	if ((*argument) == NULL)
		(*argument) = getenv("HOME");
	if (*(*argument) == '~')
	{
		if (*(*argument) + 1 == '/' || *(*argument) + 1 == '\0')
		{
			(*argument) = ft_strjoin(getenv("HOME"), (*argument) + 1);
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

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		*current_dir = '\0';
	if (ft_check_argument(&argument) == 1)
		return (1);
	if (chdir(argument) == -1)
		return (perror("cd"), 1);
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		write(2, "syntax not supported\n", 21);
	ft_add_old_pwd(envp, getcwd(buf, sizeof(buf)));
	ft_strlcpy(last_dir, current_dir, ft_strlen(current_dir));
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_env	*envp;
	t_env	*head;

	envp = ft_check_env(env);
	head = envp;
	printf("=======Before=======\n");
	while (head != NULL)
		(1) && (printf("%s\n", head->value), head = head->next);
	ft_cd(av[1], envp);
	head = envp;
	printf("\n\n=======After=======\n");
	while (head != NULL)
		(1) && (printf("%s\n", head->value), head = head->next);
}
