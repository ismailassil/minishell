/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:52:19 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/19 02:29:09 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../minishell.h"

void	mingle_data(char **container, char **buffer, char **keeper)
{
	char	*new_buff;

	if (*keeper)
	{
		new_buff = str_join(keeper, *buffer);
		if (!new_buff)
		{
			(free(*container), *container = NULL);
			return ;
		}
		if (*buffer)
			(free(*buffer), *buffer = NULL);
		*buffer = new_buff;
	}
	if (encounter_space(*buffer))
		handle_nl(container, *buffer, keeper);
	else
	{
		*container = str_join(container, *buffer);
		if (!*container)
			(free(*keeper), *keeper = NULL);
	}
}

int	allocate_buffer(char **buffer, char **keeper)
{
	*buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!*buffer)
		return (free(*keeper), *keeper = NULL, 0);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*keeper;
	char		*container;
	int			readed;

	container = NULL;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 || (size_t)BUFFER_SIZE > INT_MAX)
		return (free(keeper), keeper = NULL, NULL);
	if (!allocate_buffer(&buffer, &keeper))
		return (NULL);
	readed = read(fd, buffer, BUFFER_SIZE);
	while (readed > 0 || keeper)
	{
		buffer[readed] = '\0';
		mingle_data(&container, &buffer, &keeper);
		if (!container)
			return (free(buffer), NULL);
		if (encounter_space(container))
			break ;
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (free(keeper), keeper = NULL, free(buffer), NULL);
	}
	free (buffer);
	return (container);
}
