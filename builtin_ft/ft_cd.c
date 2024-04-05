/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/04/05 01:59:07 by iassil           ###   ########.fr       */
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

int	ft_cd(char *argument, t_struct **strp)
{
	t_info_cd	info;

	if (argument && argument[0] == '\0')
		return (0);
	info.tmp = NULL;
	if (getcwd(info.current_dir, sizeof(info.current_dir)) == NULL)
		*info.current_dir = '\0';
	info.dir = ft_check_argument(argument);
	if (info.dir == NULL)
		return ((*strp)->status = 1, 1);
	if (chdir(info.dir) == -1)
		return (ft_error("msh: cd: "), perror(info.dir), \
			free(info.dir), (*strp)->status = 1, 1);
	if (getcwd(info.buf, sizeof(info.buf)) != NULL)
		(1) && ((*strp)->status = 0, info.buffer = ft_strdup(info.buf));
	else
	{
		(ft_error("msh: cd: "), perror(argument));
		info.cwd = ft_get_cwd(&(*strp)->env);
		info.tmp = ft_strjoin_(info.cwd, "/");
		info.buffer = ft_strjoin_(info.tmp, argument);
		(free(info.tmp), free(info.cwd));
		(*strp)->status = 0;
	}
	ft_add_current_pwd(&(*strp)->env, info.buffer);
	ft_add_old_pwd(&(*strp)->env, info.current_dir);
	return (free(info.buffer), free(info.dir), 0);
}
