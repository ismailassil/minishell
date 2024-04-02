/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:09:46 by iassil            #+#    #+#             */
/*   Updated: 2024/04/02 00:47:03 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_slash(char **cmd)
{
	int		len;
	char	*ptr;

	len = ft_strlen(*cmd);
	if (len != 0 && (*cmd)[len - 1] == '/')
	{
		ptr = ft_substr(*cmd, 0, len - 1);
		ft_check_allocation(ptr);
	}
	else
	{
		ptr = ft_strdup(*cmd);
		ft_check_allocation(ptr);
	}
	return (ptr);
}

void	ft_check_rest(char *cmd, t_struct *strp,
			t_cont *cont, struct stat file_stat)
{
	char	*ptr;

	ptr = ft_remove_slash(&cmd);
	if (access(ptr, F_OK) == 0 && S_ISREG(file_stat.st_mode) == 0)
	{
		free(ptr);
		ft_stat(cmd, ": Not a directory\n", strp, cont);
		exit(126);
	}
	else
	{
		free(ptr);
		ft_stat(cmd, ": No such file or directory\n", strp, cont);
		exit(127);
	}
	free(ptr);
}

void	ft_check_path_cmd(char **envp_path, char *cmd,
			t_struct *strp, t_cont *cont)
{
	struct stat	file_stat;

	stat(cmd, &file_stat);
	if (access(cmd, F_OK) == 0 && stat(cmd, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			*envp_path = ft_strdup(cmd);
		else if (S_ISDIR(file_stat.st_mode))
			(ft_stat(cmd, ": is a directory\n", strp, cont), exit(126));
		else
			(ft_stat(cmd, ": command not found\n", strp, cont), exit(127));
	}
	else
		ft_check_rest(cmd, strp, cont, file_stat);
}
