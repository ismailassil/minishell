/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 23:12:33 by iassil            #+#    #+#             */
/*   Updated: 2024/04/06 03:16:43 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_question_mark_here_doc(t_expand *exp, char *s,
	int *i, t_struct *strp)
{
	char	*num;

	num = ft_itoa(strp->status);
	exp->new_str = ft_join_(s, num);
	*i += 1;
	free(s);
	free(num);
}

void	ft_special_chars_here_doc(t_expand *exp,
	char *arg, int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (arg[(*i) + 1] == '-')
	{
		(1) && (exp->new_str = ft_join_(s, "himBH"), *i += 1);
		free(s);
	}
	else if (arg[(*i) + 1] == '?')
		ft_question_mark_here_doc(exp, s, i, strp);
	else if (exp->quote == '\"' && arg[(*i) + 1] == '\"')
		ft_append_char(&exp->new_str, '$');
	else
		ft_append_char(&exp->new_str, '$');
}

int	ft_handle_irregulare_cases_here_doc(t_expand *exp, char *arg,
	int *i, t_struct *strp)
{
	char	*s;

	s = exp->new_str;
	if (ft_isdigit(arg[(*i) + 1]))
	{
		if (arg[(*i) + 1] == '0')
		{
			exp->new_str = ft_join_(s, "minishell");
			free(s);
		}
		return ((*i += 2), 1);
	}
	else if (!ft_check_if_chars_digit(arg[(*i) + 1]))
	{
		ft_special_chars_here_doc(exp, arg, i, strp);
		return ((*i += 1), 1);
	}
	return (0);
}

void	ft_sig_quit(int sig)
{
	(void)sig;
	rl_redisplay();
	return ;
}

void	ft_check_dollar_sign_here_doc(char **line, int pipefd,
	t_struct *strp, int flag)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(*line, '$') && ft_check_brackets(*line) == 1 && flag == 0)
	{
		ft_putstr("msh: ", pipefd);
		ft_putstr(*line, pipefd);
		(free(*line), *line = NULL);
		*line = ft_strdup(": bad substitution");
	}
	else if (ft_strchr(*line, '$') && flag == 0)
	{
		tmp = ft_strdup(*line);
		(free(*line), *line = NULL);
		*line = ft_handle_expand_for_here_doc(strp, tmp);
		(free(tmp), tmp = NULL);
	}
}
