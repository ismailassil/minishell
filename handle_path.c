/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:19 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/15 17:36:58 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_chr(char *s)
{
	int		i;
	int		j;
	char	*path;

	path = "PATH=";
	i = 0;
	while (s[i])
	{
		j = 0;
		while (path[j] && (path[j] == s[i + j]))
			j++;
		if (j == 5)
			return (1);
		i++;
	}
	return (0);
}

char	*substr(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (s + i + 1);
}

char	**handle_paths(t_env *env)
{
	int		i;
	char	*path;

	i = 0;
	while (env)
	{
		if (str_chr(env->value))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	path = substr(env->value);
	return (ft_split(path, ':'));
}
