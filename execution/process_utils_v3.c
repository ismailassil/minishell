/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_v3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:05:56 by iassil            #+#    #+#             */
/*   Updated: 2024/04/29 09:36:37 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_evar(int is_var, int is_quote, char *str)
{
	if (str && is_var == 1 && is_quote != 1 && str[0] == '\0')
		return (1);
	return (0);
}

char	**ft_fill_again(t_cont *c, int *st)
{
	t_fill_again	f;

	(1) && (f.i = 0, f.j = 0, f.count = 0);
	while (c->arg && c->arg[f.i] != 0)
	{
		if (ft_evar(c->arg_is_var[f.i], c->arg_is_quote[f.i], c->arg[f.i]))
			f.i++;
		else
			(1) && (f.count++, f.i++);
	}
	f.args = malloc((f.count + 1) * sizeof(char *));
	ft_check_allocation(f.args);
	(*st)++;
	while (c->arg && c->arg[*st] != 0)
	{
		if (ft_evar(c->arg_is_var[*st], c->arg_is_quote[*st], c->arg[*st]))
			(*st)++;
		else
		{
			f.args[f.j] = ft_strdup(c->arg[*st]);
			ft_check_allocation(f.args[f.j]);
			(1) && (f.j++, (*st)++);
		}
	}
	return (f.args[f.j] = 0, ft_f(c->arg), f.args);
}

void	ft_check_first_cmd(char **cmd, t_cont *c)
{
	int	i;

	i = 0;
	if (*cmd && c->cmd_is_var == 1 && c->cmd_is_quote != 1
		&& (*cmd)[0] == '\0')
	{
		while (c->arg && c->arg[i])
		{
			if (ft_evar(c->arg_is_var[i], \
				c->arg_is_quote[i], c->arg[i]))
				i++;
			else
				break ;
		}
		if (c->arg[i] != 0)
		{
			free(*cmd);
			*cmd = ft_strdup(c->arg[i]);
			c->arg = ft_fill_again(c, &i);
		}
		else if (c->arg[i] == 0)
			exit(SUCCESS);
	}
}

int	ft_check_env_path(t_struct *strp, char *cmd, int *status)
{
	t_env	*envp;

	envp = strp->env;
	while (envp)
	{
		if (ft_strncmp(envp->value, "PATH=", 5) == 0)
			if (ft_strlen(envp->value) > 5)
				return (false);
		envp = envp->next;
	}
	(ft_error("msh: "), ft_error(cmd), ft_error(FNF));
	return (*status = 127, true);
}

void	ft_get_exit_status(t_info *info, int nr_cont, t_struct *strp)
{
	t_exit	e;

	(1) && (info->i = 0, e.flag = 0);
	while (info->i < nr_cont)
	{
		(1) && (e.status = 0, strp->status = 0);
		waitpid(info->id[info->i++], &e.status, 0);
		if (WIFEXITED(e.status))
			strp->status = WEXITSTATUS(e.status);
		else if (WIFSIGNALED(e.status))
		{
			if (WTERMSIG(e.status) == SIGQUIT)
			{
				if (info->i == nr_cont)
					ft_putstr("Quit: 3\n", 1);
				strp->status = 131;
			}
			else if (WTERMSIG(e.status) == SIGINT)
			{
				if (e.flag == 0)
					ft_putstr("\n", 1);
				(1) && (strp->status = 130, e.flag = 1);
			}
		}
	}
}
