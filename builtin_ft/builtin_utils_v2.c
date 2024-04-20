/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:43:17 by iassil            #+#    #+#             */
/*   Updated: 2024/04/20 16:12:26 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add_new_arg(t_append_export	*f)
{
	char	*ptr;

	ptr = malloc((ft_strlen(f->value) + 1) * sizeof(char));
	ft_check_allocation(ptr);
	while (f->value && f->value[f->i] != '\0')
	{
		if (f->value[f->i] == '+')
			f->i++;
		else
			ptr[f->j++] = f->value[f->i++];
	}
	ptr[f->j] = '\0';
	return (ptr);
}

void	ft_quotes_wildcard(char **arg)
{
	char	*tmp;

	if (*arg && ft_strchr((*arg), '*')
		&& (ft_strchr((*arg), '"') || ft_strchr((*arg), '\'')))
	{
		tmp = ft_trim_quotes(*arg);
		free(*arg);
		*arg = tmp;
	}
}

void	ft_handle_error(t_info_cd *f, char *arg, t_struct **s)
{
	f->cwd = ft_get_cwd(&(*s)->env);
	ft_error(RETRIVING_CD);
	ft_error(RETRIVING_C1);
	ft_error(RETRIVING_C2);
	f->tmp = ft_join_(f->cwd, "/");
	f->buff = ft_join_(f->tmp, arg);
	(free(f->tmp), free(f->cwd));
	(*s)->status = 0;
}
