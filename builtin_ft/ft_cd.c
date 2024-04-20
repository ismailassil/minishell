/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/04/20 14:53:23 by iassil           ###   ########.fr       */
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
		return (free(arg), write(2, "msh: cd: HOME not set\n", 22), NULL);
	else if (argument == NULL || argument[0] == '\0')
	{
		free(arg);
		arg = ft_strdup(getenv("HOME"));
		if (!arg)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
	else if (argument[0] == '~' || argument[0] == '-')
		return (free(arg), write(2, "msh: cd: syntax not supported\n", 30),
			NULL);
	return (arg);
}

static void	ft_add_cpwd(t_env **envp, char *argument)
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
			ft_check_allocation(tmp);
			head->value = tmp;
			flag = 1;
			break ;
		}
		head = head->next;
	}
	ft_add_if_not_found(envp, flag, argument, "PWD=");
}

static void	ft_add_opwd(t_env **envp, char *argument)
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
			ft_check_allocation(tmp);
			head->value = tmp;
			flag = 1;
			break ;
		}
		head = head->next;
	}
	ft_add_if_not_found(envp, flag, argument, "OLDPWD=");
}

int	ft_cd(char *arg, t_struct **s)
{
	t_info_cd	f;

	if (arg && arg[0] == '\0')
		return (0);
	(1) || (f.tmp = NULL, f.errt = NULL);
	f.dirp = opendir(arg);
	if (f.dirp == NULL)
		return (ft_error("msh: cd: "), perror(arg), (*s)->status = 1, 1);
	(void)closedir(f.dirp);
	if (getcwd(f.current_dir, sizeof(f.current_dir)) == NULL)
		*f.current_dir = '\0';
	f.dir = ft_check_argument(arg);
	if (f.dir == NULL)
		return ((*s)->status = 1, 1);
	if (chdir(f.dir) == -1)
		return (ft_error("msh: cd: "), perror(f.dir), \
			free(f.dir), (*s)->status = 1, 1);
	if (getcwd(f.buf, sizeof(f.buf)) != NULL)
		(1) && ((*s)->status = 0, f.buff = ft_strdup(f.buf));
	else
		ft_handle_error(&f, arg, s);
	(ft_add_cpwd(&(*s)->env, f.buff), ft_add_opwd(&(*s)->env, f.current_dir));
	return (free(f.buff), free(f.dir), 0);
}
