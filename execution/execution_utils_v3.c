/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_v3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:15:13 by iassil            #+#    #+#             */
/*   Updated: 2024/03/31 20:16:20 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_cont_and_cmd(t_cont *cont, \
	t_struct *strp, t_info *info, int nr_cont)
{
	if (cont == NULL)
		return (1);
	if (nr_cont == 1 && cont->cmd == NULL)
	{
		ft_open_files(cont, info, strp);
		return (1);
	}
	if (nr_cont == 1 && ft_builtin_exist(cont) == 1)
	{
		if (ft_open_files(cont, info, strp) == 1)
			return (1);
		ft_check_commands(cont, strp, info, 1);
		return (1);
	}
	return (0);
}

void	ft_exitf(t_struct **strp, t_cont **cont)
{
	ft_free_env(&(*strp)->env);
	ft_free_containers(cont);
}

void	ft_stat(char *cmd, char *str, t_struct *strp, t_cont *cont)
{
	ft_error("msh: ");
	ft_error(cmd);
	ft_error(str);
	ft_exitf(&strp, &cont);
	free(strp);
}
