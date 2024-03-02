/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 16:58:09 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_cd(char *argument)
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
	ft_strlcpy(last_dir, current_dir, ft_strlen(current_dir));
	return (0);
}
