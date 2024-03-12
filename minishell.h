/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musashi <musashi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:57 by iassil            #+#    #+#             */
/*   Updated: 2024/03/12 15:49:13 by musashi          ###   ########.fr       */
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
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <limits.h>
# define SUCCESS	0
# define FAIL		1
# define CMD		0
# define PIPE		1
# define OUTFILE	2
# define INFILE		3
# define APPEND		4
# define HEREDOC	5
# define FILENAME	6
# define ARG		7
# define DELIMITER	8
# define MAX		1024
# define GREEN		"\x1b[1;32m"
# define YELLOW_	"\x1b[0;33m"
# define YELLOW		"\x1b[1;33m"
# define RED		"\x1b[1;31m"
# define BLUE		"\x1b[1;34m"
# define MAGENTA	"\x1b[1;35m"
# define CYAN		"\x1b[1;36m"
# define WHT		"\e[1;37m"
# define RESET		"\x1b[0m"

typedef struct s_start_end
{
	int	start;
	int	end;
}		t_stend;

typedef struct s_c
{
	int	i;
	int	j;
	int	quote;
}		t_c;

typedef struct s_expand
{
	int		quote;
	char	*expa;
	char	*new_str;
	char	*s;
}			t_expand;

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

typedef struct s_count
{
	int	arg;
	int	infile;
	int	outfile;
	int	append;
}		t_count;

typedef struct s_tmp_cont
{
	char	*cmd;
	char	**arg;
	char	**infile;
	char	**outfile;
	char	**append;
}			t_tmp_cont;

typedef struct s_container
{
	char				*cmd;
	char				**arg;
	char				**infile;
	char				**outfile;
	char				**append;
	struct s_container	*next;
}						t_cont;

/*==========BUILTIN FUNCIONS==========*/
int		ft_cd(char *argument, t_env **envp);
void	ft_echo(int n, char *argument);
void	ft_env(t_env *envp);
void	ft_exit(void);
int		ft_export(char *argument, t_env *envp);
void	ft_pwd(void);
void	ft_unset(t_env *envp, char *argument);
// Utils function for builtin function
t_env	*ft_get_env(char **env);
void	ft_print_exported_variable(t_env *envp);
void	ft_add_current_pwd(t_env **envp, char *argument);
void	ft_add_old_pwd(t_env **envp, char *argument);

/*==========PARSING FUNCIONS==========*/
char	*ft_add_space_to_input(char *input);
void	ft_split_tokens(t_token **head, char *str);
void	ft_tokenize(t_token **str);
void	ft_expand_argument(t_env *env, t_token **linked_list);
bool	ft_check_syntax(t_token *str);
void	ft_remove_quotes(t_token **linked_list);
// Utils function for Parsing
void	ft_error(char *str);
void	ft_append_char(char **str, int c);
char	*ft_allocate_for_var(int flag, char *str, int i);
int		ft_handle_inregulare_cases(t_expand *exp, int c, int *i);
int		ft_check_quotes(char *str);

/*==========EXECUTION FUNCIONS==========*/
void	ft_execution(t_token **token);

/*==========UTILS FUNCIONS==========*/
int		ft_check_if_chars_digit(int c);
void	ft_print(t_token *lst);
void	ft_print_types(t_token *str);
void	ft_print_container(t_cont *head);

/*==========SIGNAL FUNCIONS==========*/
void	ft_signal_handler(void);
void	ctrl_c(int sig);
void	ctrl_slash(int sig);
void	ft_disable_attr(void);

/*==========ENV LINKED LIST UTILS FUNCIONS==========*/
int		ft_t_env_len(t_env *head);
int		ft_push_value(char *value, t_env **head);
void	ft_free_env(t_env **head);

/*==========CONTAINER LINKED LIST UTILS FUNCIONS==========*/
int		ft_t_cont_len(t_cont *head);
int		ft_push_container(t_tmp_cont *tmp, t_cont **head);
void	ft_free_containers(t_cont **head);
t_cont	*ft_new_node_for_cont(t_tmp_cont *tmp);

/*==========TOKEN LINKED LIST UTILS FUNCIONS==========*/
int		ft_t_token_len(t_token *head);
int		ft_push_token(char *token, t_token **head);
void	ft_free_tokens(t_token **head);

/*==========LIBFT FUNCIONS==========*/
t_cont	*ft_lstnew(void *content);
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
char	*ft_strjoin_(char *str1, char *str2);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);

#endif
