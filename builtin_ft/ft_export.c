/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:07 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 18:00:51 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fetch_export_arguments(char *arg, char **name, char **value)
{
	int	index;
	int	i;

	while (arg[i] != '\0')
	{
		index = 0;
		while (arg[i] != '=' && arg[i] != '\0')
			(index++, i++);
		*name = ft_substr(arg, i - index, index);
		if (!*name)
			return (1);
		if (arg[i] == '=')
			i++;
		index = 0;
		while ((arg[i] != '\'' || arg[i] != '\"') && arg[i] != '\0')
			(index++, i++);
		*value = ft_substr(arg, i - index, index);
		if (!*value)
			return (1);
	}
	return (0);
}

int	ft_export(char *argument)
{
	char	*name;
	char	*value;

	if (ft_fetch_export_arguments(argument, &name, &value) == 1)
		return (1);
	return (0);
}
