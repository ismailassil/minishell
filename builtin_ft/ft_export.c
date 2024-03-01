/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:07 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 21:49:14 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fetch_arguments(char *arg, char **name, char **value)
{
	int	index;
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		index = 0;
		while (arg[i] != '=' && arg[i] != '\0')
			(index++, i++);
		if (arg[i] == '=')
			i++;
		*name = ft_substr(arg, i - index, index);
		if (!*name)
			return (1);
		if (arg[i] == '\'' || arg[i] == '\"')
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

size_t	ft_strlenptr(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	ft_export(char *argument, char ***env)
{
	char	*name;
	char	*value;
	char	**envp;
	int		i;

	i = 0;
	if (ft_fetch_arguments(argument, &name, &value) == 1)
		return (1);
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp(name, (*env)[i], ft_strlen(name)) == 0)
		{
			(*env)[i] = ft_strjoin(name, value);
			if (!(*env)[i])
				return (1);
			return (0);
		}
		i++;
	}
	i = 0;
	envp = (char **)malloc((ft_strlenptr(*env) + 2) * sizeof(char *));
	if (!envp)
		return (1);
	envp[ft_strlenptr(*env) + 2] = NULL;
	while ((*env)[i] != NULL)
		(1) && (envp[i] = ft_strdup((*env)[i]), i++);
	envp[i] = ft_strjoin(name, value);
	if (!envp[i])
		return (1);
	*env = envp;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ft_export("SAYMYNAME='ismail'", &env) == 1)
		printf("Error\n");
	while (*env)
		(printf("%s\n", *env), env++);
}
