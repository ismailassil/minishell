/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:40:17 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/04 15:27:00 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**ft_split(char const *s, char c);

typedef struct start_end
{
	int	start;
	int	end;
}	t_stend;

typedef struct tree_st
{
	char			*cmd;
	struct tree_st	*left;
	struct tree_st	*right;
}	t_tree;

/**
 * 0 = option
 * 1 = cmd
 * 2 = operator
*/

typedef struct tokens
{
	char			*token;
	int				type;
	struct tokens	*next;
}	t_token;

int		push(char *token, t_token **head);

#endif