/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaksfinder.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:10:39 by iassil            #+#    #+#             */
/*   Updated: 2024/04/02 16:30:44 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Header file*/
/*==== LEAKS FINDER ====*/
#include <libc.h>

FILE	*gfp;

static void	*__malloc(size_t size, int line, const char *file)
{
	void	*ptr;

	ptr = malloc(size);
	fprintf(gfp, "dct[%p] = ['malloc', '%p', %i, '%s']\n", 
		ptr, ptr, line, file);
	fflush(gfp);
	return (ptr);
}

static void	__free(void *ptr, int line, const char *file)
{
	fprintf(gfp, "dct[%p] = ['free', '%p', %i, '%s']\n",
		ptr, ptr, line, file);
	fflush(gfp);
	free(ptr);
}
/**/
# define malloc(x) __malloc(x, __LINE__, __FILE__)
# define free(x) __free(x, __LINE__, __FILE__)
/*======================*/

/*Source file*/
void	leaks()
{
	fclose(gfp);
	system("leaks minishell");
	usleep(1000 * 100 *10000);
}

int	main(void)
{
	gfp = fopen("leaks.t", "w");
	atexit(leaks);
}
