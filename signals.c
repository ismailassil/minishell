/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:26 by iassil            #+#    #+#             */
/*   Updated: 2024/02/29 16:10:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ctrl_c_handler(int sig)
{
	(void)sig;
}

void ctrl_d_handler(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

void ctrl___handler(int sig)
{
	(void)sig;
}
