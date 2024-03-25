/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils_v1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:32:41 by iassil            #+#    #+#             */
/*   Updated: 2024/03/24 19:56:51 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	Checks if a char is a special character or not
*/
int	ft_check_if_chars_digit(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

/*
*	Checks if an allocation failed or not
*/
void	ft_check_allocation(void *str)
{
	if (str == NULL)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
}

/*
*	Checks if a syscall failed or not
*/
void	ft_syscall(int return_, char *str)
{
	if (return_ == -1)
		(perror(str), exit(FAIL));
}

/*
*	Checks if a (signal) syscall failed or not
*/
void	ft_sig(void *return_, char *str)
{
	if (return_ == SIG_ERR)
		(perror(str), exit(FAIL));
}
