/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:49:09 by iassil            #+#    #+#             */
/*   Updated: 2024/04/20 11:41:00 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_last(char *input, char *curdir)
{
	t_indexing	d;

	(1) && (d.i = ft_strlen(input) - 1, d.j = ft_strlen(curdir) - 1);
	while (d.i != 0 && d.j != 0)
	{
		if (input[d.i] == '*')
		{
			while (d.i != 0 && input[d.i] == '*')
				d.i--;
			if (d.i <= 0)
				return (1);
			while (d.j > 0 && curdir[d.j] != input[d.i])
				d.j--;
		}
		if (d.i != 0 && d.j != 0 && input[d.i] == curdir[d.j])
			(1) && (d.i--, d.j--);
		else
			return (0);
	}
	return (1);
}

int	ft_check_default(char *input, char *curdir)
{
	t_indexing	d;

	(1) && (d.i = 0, d.j = 0);
	while (input[d.i] && curdir[d.j])
	{
		if (input[d.i] == '*')
		{
			while (input[d.i] && input[d.i] == '*')
				d.i++;
			if (input[d.i] == '\0')
				return (1);
			while (curdir[d.j] && curdir[d.j] != input[d.i])
				d.j++;
		}
		if (input[d.i] == curdir[d.j])
			(1) && (d.i++, d.j++);
		else
			return (0);
	}
	if (input[d.i] != '\0' && curdir[d.j] == '\0')
		return (0);
	return (1);
}

int	ft_check_dir(char *input, char *curdir)
{
	if (input[ft_strlen(input) - 1] != '*')
	{
		if (!ft_check_last(input, curdir))
			return (0);
	}
	else
	{
		if (!ft_check_default(input, curdir))
			return (0);
	}
	return (1);
}

int	ft_check_input(char *input)
{
	int	i;
	int	quote;
	int	flag;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			flag = 1;
			i++;
		}
		while (flag == 1 && input[i] != quote && input[i] != '\0')
		{
			if (input[i] == '*')
				return (1);
			i++;
		}
		if (flag == 1 && input[i] == quote)
			(1) && (flag = 0, quote = 0);
		if (input[i])
			i++;
	}
	return (0);
}

char	**ft_wildcards(char **input)
{
	t_wildcards	w;

	w.i = 0;
	if (!input || !*input)
		return (NULL);
	if (ft_check_input(*input))
		return (NULL);
	ft_rm_quotes(input);
	w.dirs = malloc(PATH_MAX * sizeof(char *));
	ft_check_allocation(w.dirs);
	w.dirp = opendir(".");
	if (w.dirp == NULL)
		return (perror("opendir"), NULL);
	w.name = readdir(w.dirp);
	while (w.name != NULL)
	{
		if (w.name->d_name[0] != '.' && ft_check_dir(*input, w.name->d_name))
			w.dirs[w.i++] = ft_strdup(w.name->d_name);
		w.name = readdir(w.dirp);
	}
	w.dirs[w.i] = 0;
	return ((void)closedir(w.dirp), w.dirs);
}
