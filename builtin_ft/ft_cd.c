/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:33:58 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 17:36:56 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *argument)
{
	char		current_dir[PATH_MAX];
	char		buf[PATH_MAX];
	static char	last_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		*current_dir = '\0';	
	if (argument == NULL)
		argument = getenv("HOME");
	if (*argument == '~')
	{
		if (*argument + 1 == '/' || *argument + 1 == '\0')
			argument = ft_strjoin(getenv("HOME"), argument + 1);
		else
		{
			write(2, "syntax not supported\n", 21);
			return (1);
		}
	}
	if (chdir(argument) == -1)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		printf("Error\n");
	ft_strlcpy(last_dir, current_dir, ft_strlen(current_dir));
	return (0);
}
