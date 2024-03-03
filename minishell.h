/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:57 by iassil            #+#    #+#             */
/*   Updated: 2024/03/03 17:55:17 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/syslimits.h>
# define CMD		0
# define PIPE		1
# define OUTFILE	2
# define INFILE		3
# define APPEND		4
# define HEREDOC	5
# define FILENAME	6
# define ARG		7
# define DELIMITER	8
# define GREEN		"\x1b[1;32m"
# define YELLOW_	"\x1b[0;33m"
# define YELLOW		"\x1b[1;33m"
# define RED		"\x1b[1;31m"
# define BLUE		"\x1b[1;34m"
# define MAGENTA	"\x1b[1;35m"
# define CYAN		"\x1b[1;36m"
# define WHT		"\e[1;37m"
# define RESET		"\x1b[0m"

typedef struct start_end
{
	int	start;	
	int	end;	
}		t_stend;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_tokens
{
	char			*token;
	int				type;
	struct s_tokens	*next;
}					t_token;

typedef struct s_container
{
	char				*holder;
	int					type;
	struct s_container	*next;
}						t_cont;

void	ft_print_types(t_token *str);

/*==========BUILTIN FUNCIONS==========*/
void	ft_exit(void);
int		ft_cd(char *path);
void	ft_pwd(void);

/*==========PARSING FUNCIONS==========*/
char	*ft_add_space_to_input(char *input);
void	init_tokens(t_token **head, char *str);
void	ft_tokenize(t_token **str);
void	ft_check_syntax(t_token *str);

/*==========SIGNAL FUNCIONS==========*/
void	ft_signal_handler(void);
void	ctrl_c_handler(int sig);
void	ctrl_d_handler(int sig);
void	ctrl___handler(int sig);

/*==========LIBFT FUNCIONS==========*/
t_cont	*ft_lstnew(void *content);
int		push(char *token, t_token **head);
void	ft_lstadd_back(t_cont **lst, t_cont *_new);
void	ft_lstadd_front(t_cont **lst, t_cont *_new);
void	ft_lstdelone(t_cont *lst, void (*del)(void *));
void	ft_lstclear(t_cont **lst, void (*del)(void *));
void	ft_lstiter(t_cont *lst, void (*f)(void *));
int		ft_lstsize(t_cont *lst);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);

#endif
