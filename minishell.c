/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:06 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 17:22:12 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(t_container *lst)
{
	t_container	*head = lst;

	while (head != NULL)
	{
		printf("====={%s}=====\n", head->holder);
		head = head->next;
	}
}

void	ft_parse_input_from_shell(char *input)
{
	int			i;
	int			index;
	t_container	**spart;

	spart = NULL;
	(1) && (i = 0, index = 0);
	while (input[i] != '\0')
	{
		while (input[i] == ' ' && input[i] != '\0')
			i++;
		index = 0;
		while (input[i] != ' ' && input[i] != '\0')
			(index++, i++);
		char *oo = ft_substr(input, i - index, index);
		printf("%s\n", oo);
		ft_lstadd_back(spart, ft_lstnew(oo));
	}
	ft_print(*spart);
}

int	main(void)
{
	char	*line;

	while (true)
	{
		line = readline(YELLOW"minishell$ "RESET);
		if (line == NULL)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parse_input_from_shell(line);
		free(line);
	}
}
