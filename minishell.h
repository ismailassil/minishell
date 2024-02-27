/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:57 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 17:19:46 by iassil           ###   ########.fr       */
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
# define GREEN  "\x1b[32m"
# define YELLOW "\x1b[33m"
# define RESET  "\x1b[0m"

typedef struct s_container
{
    char				*holder;
    struct s_container	*next;
}						t_container;

/*==========LIBFT FUNCIONS==========*/
t_container	*ft_lstnew(void *content);
t_container	*ft_lstlast(t_container *lst);
t_container	*ft_lstmap(t_container *lst, void *(*f)(void *), void (*del)(void *));
void	    ft_lstadd_front(t_container **lst, t_container *_new);
int	    	ft_lstsize(t_container *lst);
void	    ft_lstadd_back(t_container **lst, t_container *_new);
void	    ft_lstdelone(t_container *lst, void (*del)(void *));
void	    ft_lstclear(t_container **lst, void (*del)(void *));
void	    ft_lstiter(t_container *lst, void (*f)(void *));
int	    	ft_isalpha(int c);
int	    	ft_isdigit(int c);
int	    	ft_isalnum(int c);
int	    	ft_isascii(int c);
int	    	ft_isprint(int c);
int	    	ft_toupper(int c);
int	    	ft_tolower(int c);
int	    	ft_strncmp(const char *s1, const char *s2, size_t n);
int	    	ft_atoi(const char *str);
int	    	ft_memcmp(const void *s1, const void *s2, size_t n);
void	    *ft_memset(void *b, int c, size_t len);
void	    ft_bzero(void *s, size_t n);
void	    *ft_memmove(void *dst, const void *src, size_t len);
void	    *ft_memcpy(void *dst, const void *src, size_t n);
void	    *ft_memchr(const void *s, int c, size_t n);
void	    *ft_calloc(size_t count, size_t size);
char	    *ft_strchr(const char *str, int c);
char	    *ft_strrchr(const char *str, int c);
char	    *ft_strnstr(const char *haystack, const char *needle, size_t len);
char	    *ft_strdup(const char *s1);
size_t	    ft_strlen(const char *str);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	    ft_strlcat(char *dst, const char *src, size_t dstsize);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
char	    *ft_strtrim(char const *s1, char const *set);
char	    *ft_strjoin(char const *s1, char const *s2);
char	    *ft_itoa(int n);
char	    *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	    ft_striteri(char *s, void (*f)(unsigned int, char*));
void	    ft_putchar_fd(char c, int fd);
void	    ft_putstr_fd(char *s, int fd);
void	    ft_putendl_fd(char *s, int fd);
void	    ft_putnbr_fd(int n, int fd);
char	    **ft_split(char const *s, char c);

#endif
