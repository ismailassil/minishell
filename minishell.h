/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:20:57 by iassil            #+#    #+#             */
/*   Updated: 2024/04/29 15:51:01 by iassil           ###   ########.fr       */
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
# include <sys/fcntl.h>
# include <sys/syslimits.h>
# include <sys/stat.h>
# include <dirent.h>
# define SUCCESS		0
# define FAIL			1
# define CMD			0
# define PIPE			1
# define OUTFILE		2
# define INFILE			3
# define APPEND			4
# define HEREDOC		5
# define FILENAME		6
# define ARG			7
# define DELIMITER		8
# define CHILD			0
# define ALLCHILDS		-1
# define BAD_SUB		11
# define CR				O_CREAT
# define WO				O_WRONLY
# define AP				O_APPEND
# define SQ				-20
# define RETRIVING_CD	"msh: error retrieving current directory: "
# define RETRIVING_C1	"getcwd: cannot access parent directories: "
# define RETRIVING_C2	"No such file or directory\n"
# define FNF			": No such file or directory\n"
# define MS				": numeric argument required\n"
# define AMB			": ambiguous redirect\n"
# define GREEN			"\x1b[1;32m"
# define YELLOW_		"\x1b[0;33m"
# define YELLOW			"\x1b[1;33m"
# define RED			"\x1b[1;31m"
# define BLUE			"\x1b[1;34m"
# define MAGENTA		"\x1b[1;35m"
# define CYAN			"\x1b[1;36m"
# define WHT			"\e[1;37m"
# define RESET			"\x1b[0m"

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

typedef struct s_check_file_name
{
	int							i;
	char						*before;
	char						*after;
	char						**vars;
	int							status;
	struct s_check_file_name	*next;
}								t_file;

typedef struct s_del
{
	char	*ptr;
	int		flag;
	int		i;
	int		j;
	int		count;
	int		len;
	int		quote;
	int		is_dollar;
}			t_del;

typedef struct s_info_here_doc
{
	char	*line;
	char	*delimiter;
	char	*ch_delimiter;
	char	*push;
	int		flag;
}			t_info_here_doc;

typedef struct s_cc
{
	int	i;
	int	j;
	int	z;
	int	y;
	int	h;
}		t_cc;

typedef struct s_brackets
{
	int	i;
	int	c;
	int	count;
	int	c_left;
}		t_brackets;

typedef struct s_expand
{
	int		quote;
	char	*expa;
	char	*new_str;
	char	*s;
}			t_expand;

typedef struct s_info_cd
{
	char	current_dir[PATH_MAX];
	char	buf[PATH_MAX];
	char	*buff;
	char	*tmp;
	char	*cwd;
	char	*dir;
	char	*errt;
	DIR		*dirp;
}			t_info_cd;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shlvl
{
	t_env	*env;
	int		flag;
	int		num;
	char	*new_value;
	char	*tmp;
}			t_shlvl;

typedef struct s_struct
{
	int		status;
	int		nr_cont;
	int		is_filename;
	t_env	*env;
	t_file	*head;
	t_file	*current;
}			t_struct;

typedef struct s_path
{
	char	**path;
	t_env	*head;
	char	*envp_path;
	char	*return_path;
}			t_path;

typedef struct s_heredoc
{
	char	*line;
	char	*hold;
	char	*del;
	pid_t	id;
	int		status;
}			t_heredoc;

typedef struct s_tools
{
	char	*ptr;
	int		i;
	int		j;
	int		count;
	int		flag;
	int		quote;
	int		cquote;
}			t_tools;

typedef struct s_in
{
	int	count;
	int	i;
	int	j;
	int	flag;
	int	quote;
	int	tmp;
}		t_in;

typedef struct s_indexing
{
	int	i;
	int	j;
}		t_indexing;

typedef struct s_exit
{
	int	status;
	int	flag;
}		t_exit;

typedef struct s_count
{
	int	arg;
	int	infile;
	int	outfile;
	int	here_doc;
}		t_count;

typedef struct s_tokens
{
	char			*token;
	int				type;
	int				is_var;
	int				is_quote;
	int				findex;
	struct s_tokens	*next;
}					t_token;

typedef struct s_tokenize
{
	t_token	*head;
	int		flag;
	int		i;	
	int		index;
}			t_tokenize;

typedef struct s_tmp_cont
{
	char	*cmd;
	int		cmd_is_var;
	int		cmd_is_quote;
	char	**arg;
	int		*arg_is_var;
	int		*arg_is_quote;
	char	**inf;
	int		*out_is_var;
	int		*out_is_quote;
	char	**outf;
	int		*inf_is_var;
	int		*inf_is_quote;
	char	**here_doc;
	int		*file_or_heredoc;
	int		*out_t;
}			t_tmp_cont;

typedef struct s_container
{
	char				*cmd;
	int					cmd_is_var;
	int					cmd_is_quote;
	char				**arg;
	int					*arg_is_var;
	int					*arg_is_quote;
	char				**infile;
	int					*infile_index;
	int					*inf_is_amb;
	char				**inf_before;
	int					*infile_is_var;
	int					*infile_is_quote;
	char				**here_doc;
	int					*file_or_heredoc;
	int					*here_doc_fd;
	char				**outfile;
	int					*outfile_index;
	int					*out_is_amb;
	char				**out_before;
	int					*outfile_is_var;
	int					*outfile_is_quote;
	int					*outfile_type;
	int					nbr_files;
	struct s_container	*next;
}						t_cont;

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	here_doc;
	int	opened_fd[OPEN_MAX];
	int	len;
}		t_fd;

typedef struct s_fd_
{
	int	infile;
	int	outfile;
	int	here_doc;
	int	i;
}		t_fd_;

typedef struct s_index_files
{
	t_cont	*cont;
	t_token	*tok;
	int		outfile_len;
	int		infile_len;
	int		i;
	int		j;
	int		index_len;
	t_file	*h;
}			t_index_files;

typedef struct s_wildcards
{
	t_token			*head;
	t_token			*previous;
	t_token			*newlist;
	char			**dirs;
	int				i;
	int				is_export;
	char			*tmp;
	DIR				*dirp;
	struct dirent	*name;
}					t_wildcards;

typedef struct s_amb_rdt
{
	int		i;
	char	**ptr;
	char	*tmp;
	char	**dir;
}			t_amb_rdt;

typedef struct s_info
{
	t_fd	fd;
	int		pipe[2];
	int		nbr_cont;
	pid_t	*id;
	int		i;
}			t_info;

typedef struct s_append_export
{
	char	*ptr;
	char	*value;
	char	*tmp;
	char	*tmp1;
	int		i;
	int		j;
}			t_append_export;

typedef struct s_execve
{
	char	*cmd_path;
	char	**argv;
	char	**envp;
}			t_execve;

typedef struct s_push_middle
{
	t_token	*next_node;
	t_token	*last_node;
	t_token	*last_newlist;
	t_token	*tobefreed;
}			t_push_middle;

typedef struct s_fill_again
{
	int		i;
	int		j;
	int		count;
	char	**args;
}			t_fill_again;

typedef struct s_open_files
{
	t_cont	*cont;
	t_fd_	fd;
	int		i;
	int		o;
	int		index;
	int		nbr_files;
}			t_open_files;

typedef struct s_push_matching
{
	t_token	*newlist;
	char	*tmp;
	char	**dirs;
	int		i;
}			t_push_matching;

typedef struct s_expand_arg
{
	t_token	*head;
	t_token	*previous;
	t_token	*newlist;
	char	*tmp;
	char	*check;
	int		is_export;
	int		i;
	int		is_dollar;
}			t_expand_arg;

typedef struct s_check_filename
{
	int		i;
	int		j;
	int		flag;
	t_file	*head;
	char	*tmp;
}			t_check_filename;

/*=====Global Variable for Signal=====*/
struct termios	g_original_attr;

/*==========BUILTIN FUNCIONS==========*/
t_struct				*ft_get_struct_and_env(char **env);
int						ft_cd(char *argument, t_struct **strp);
void					ft_echo(char *argument);
void					ft_env(t_env *envp);
void					ft_exit(t_cont *cont, t_struct *strp);
int						ft_export(char *arg, t_struct *strp);
void					ft_pwd(t_env *env);
void					ft_unset(t_struct **strp, char *argument);
//	Utils function for builtin function
void					ft_print_exported_variable(t_env *envp);
char					*ft_get_cwd(t_env **envp);
bool					ft_check_syntax_export(char *arg);
char					*ft_filter_arg(char *arg);
char					*ft_add_new_arg(t_append_export	*f);
int						ft_is_n(char *str);

/*==========PARSING FUNCIONS==========*/
char					*ft_add_space_to_input(char *input);
void					ft_split_tokens(t_token **head, char *str);
void					ft_tokenize(t_token **str);
void					ft_expand_argument(t_struct *strp,
							t_token **linked_list);
bool					ft_check_syntax(t_token *str);
void					ft_remove_quotes(t_token **linked_list);
char					*ft_trim_quotes(char *str);
void					ft_update_quote(char *arg, int *i, t_expand *exp);
void					ft_init_tokens(t_token **head, char *str);
char					*ft_alloc_str(t_token **tokens, char *str,
							t_stend *cord);
t_stend					*ft_extract_start_end_of_token(char *str, int s);
char					*ft_handle_expand(t_struct *strp, char *arg);
char					*ft_handle_expand_for_here_doc(t_struct *strp,
							char *arg);
int						ft_expand_word_after_dollar(t_expand *exp, int *i,
							char *arg, t_struct *strp);
char					*ft_arg_is_exist(t_struct *strp, char *var);
int						ft_between_bracket(char *str, int i);
//					Utils function for Parsing
void					ft_error(char *str);
void					ft_append_char(char **str, int c);
char					*ft_allocate_for_var(int flag, char *str, int i);
int						ft_handle_irregulare_cases(t_expand *exp, char *c,
							int *i, t_struct *strp);
int						ft_check_quotes(char *str);
int						ft_check_brackets(char *str);
int						ft_handle_irregulare_cases_here_doc(t_expand *exp,
							char *arg, int *i, t_struct *strp);
void					ft_push_middle(t_token *previous,
							t_token **current, t_token **newlist);
void					ft_token_list(t_token *current, t_token **new_list);
t_token					*ft_split_and_push_node(t_token **current);
int						ft_check_after_expand(t_token **current, int is_quote);
void					ft_split_node(t_expand_arg *f, t_token **linked_list);
char					**ft_wildcards(char **input);
void					ft_match_wildcards(t_token **token);
int						ft_check_file_name(t_file *head);
int						ft_occurence_of_amb(t_file	*head, int *flag,
							int *i, int *j);
void					ft_add_back(t_file **lst, t_file *_new);
int						ft_is_between_quotesorequal(char *str, int f);
int						ft_surpass_cchars(char *var);
void					ft_save_var_name_and_value(t_expand_arg *f, \
							t_file **_new, t_struct *strp);
void					ft_add_val_to_vars(t_struct *strp, t_env *head, int i);
void					ft_add_to_vars(t_struct *strp);

/*==========EXECUTION FUNCIONS==========*/
void					ft_index_files(t_token *head, t_cont **container,
							t_struct *strp);
void					ft_fill_infile_outfile_here_doc(t_token *head, \
							t_tmp_cont *t, t_cc *c);
void					ft_fill_outfile_append(t_token *head, \
							t_tmp_cont *t, t_cc *c);
void					ft_allocate_tmp_cont(t_token *head, t_tmp_cont	**cont);
void					ft_allocate_for_arg_types(t_tmp_cont **cont, t_count c);
void					ft_count_(t_token *head, t_count *c);
int						ft_check_cont_and_cmd(t_cont *cont, \
							t_struct *strp, t_info *info, int nr_cont);
int						ft_here_doc(char *delimiter, t_struct *strp);
int						ft_here_doc_parsing(t_token *lst, t_struct *strp);
void					ft_execution(t_token **token, t_struct *strp);
void					ft_check_rest(char *cmd, t_struct *strp,
							t_cont *cont, struct stat file_stat);
void					ft_check_path_cmd(char **envp_path, char *cmd,
							t_struct *strp, t_cont *cont);
void					ft_execute_multiple_cmds(t_cont *cont, \
							t_struct *strp, t_info *info, int nr_cont);
int						ft_check_commands(t_cont *cont, t_struct *strp,
							t_info *info, int j);
char					**ft_join_for_envp_execve(t_env *env);
char					**ft_join_for_argv_execve(t_cont *cont);
void					ft_check_(char **envp_path, char **cmd,
							t_struct *strp, t_cont *cont);
void					ft_check_allocation(void *str);
void					ft_syscall(int return_, char *str);
void					ft_sig(void *return_, char *str);
void					ft_f(char **str);
int						ft_open_files(t_cont *c, t_info *info, t_struct *s);
void					ft_add_path_executed_cmd(char *str, t_env *env);
void					ft_return_path(char **path, char *cmd,
							t_struct *strp, t_cont *cont);
void					ft_rm_quotes(char **input);
void					ft_quotes_wildcard(char **arg);
char					*ft_trim_dollar(char *del);
bool					ft_check_del_and_quotes(char *hold);
char					*ft_trim_dollar(char *del);
char					*ft_remove_for_del(char *hold);
char					**ft_split_after_expanding(char *str);
void					ft_check_special_quote(char **str);
char					*ft_trim_special_quote(char *str);
void					ft_skip_null_args(t_cont *cont);
int						ft_check_env_path(t_struct *strp, \
							char *cmd, int *status);
void					ft_get_exit_status(t_info *info, int nr_cont, \
							t_struct *strp);

//					CONTAINER FUNCTIONS
void					ft_link_all_in_containers(t_token *head,
							t_cont **container);
void					ft_count_alc(t_token *head, t_tmp_cont **cont);
void					ft_free_tmp(t_tmp_cont **tmp);

//					BUILTINS FUNCTIONS
int						ft_builtin_exist(t_cont *cont);
void					execute_echo(t_cont *cont, t_struct **strp);
void					execute_cd(t_cont *cont, t_struct **strp);
void					execute_env(t_cont *cont, t_struct **strp);
void					execute_export(t_cont *cont, t_struct **strp);
void					execute_unset(t_cont *cont, t_struct **strp);
void					ft_add_cmd_or_arg_to_env(int nr_cont, t_cont *cont,
							t_struct *strp);
void					ft_exitf(t_struct **strp, t_cont **cont);
void					ft_stat(char *cmd, char *str,
							t_struct *strp, t_cont *cont);
int						ft_find_slash_or_point(char *cmd);
int						ft_iswhitespace(char *str);
int						ft_evar(int is_var, int is_quote, char *str);
void					ft_check_first_cmd(char **cmd, t_cont *c);
void					ft_handle_error(t_info_cd *f, char *arg, t_struct **s);
bool					ft_is_plus_exist(char *arg);
void					ft_print_rest(char *str);
bool					ft_check_if_null(t_env *env, char **str);
char					*get_env(t_env *env, char *str);

/*==========UTILS FUNCIONS==========*/
int						ft_check_if_chars_digit(int c);
void					ft_print(t_token *lst);
void					ft_print_types(t_token *str);
void					ft_print_container(t_cont *head);
void					ft_putstr(char *str, int fd);
void					ft_throw_error(char *str);

/*==========SIGNAL FUNCIONS==========*/
void					ft_signal_handler(void);
void					ctrl_c(int sig);
void					ctrl_slash(int sig);
void					ft_disable_attr(void);
void					ft_default_signals(void);
void					ft_sig_quit(int sig);
int						ft_status(int mode, int status_);

/*==========ENV LINKED LIST UTILS FUNCIONS==========*/
int						ft_t_env_len(t_env *head);
int						ft_push_value(char *value, t_env **head);
void					ft_free_env(t_env **head);
void					ft_sort_list(t_env **env);
void					ft_delete_node(t_env **env);

/*==========CONTAINER LINKED LIST UTILS FUNCIONS==========*/
int						ft_t_cont_len(t_cont *head);
int						ft_push_container(t_tmp_cont *tmp, t_cont **head);
void					ft_free_containers(t_cont **head);
t_cont					*ft_new_node_for_cont(t_tmp_cont *tmp);
int						ft_open_here_doc(t_cont *cont, t_info *info,
							t_struct *strp);
void					ft_check_dollar_sign_here_doc(char **line, int pipefd,
							t_struct *strp, int flag);

/*==========TOKEN LINKED LIST UTILS FUNCIONS==========*/
t_token					*ft_new_node(char *token);
t_token					*ft_last_node(t_token *top);
int						ft_t_token_len(t_token *head);
int						ft_push_token(char *token, t_token **head);
void					ft_free_tokens(t_token **head);
void					ft_fill_for_outfile(t_tmp_cont *tmp, \
							t_cont **_new, int *i);
void					ft_free_t_file(t_file **filename_node);

/*==========LIBFT FUNCIONS==========*/
t_cont					*ft_lstnew(void *content);
void					ft_lstadd_back(t_cont **lst, t_cont *_new);
void					ft_lstadd_front(t_cont **lst, t_cont *_new);
void					ft_lstdelone(t_cont *lst, void (*del)(void *));
void					ft_lstclear(t_cont **lst, void (*del)(void *));
void					ft_lstiter(t_cont *lst, void (*f)(void *));
int						ft_lstsize(t_cont *lst);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_atoi(const char *str);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_calloc(size_t count, size_t size);
char					*ft_strchr(const char *str, int c);
char					*ft_strrchr(const char *str, int c);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_join_(char *str1, char *str2);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
void					ft_striteri(char *s, void (*f)(unsigned int, char*));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
char					**ft_split(char const *s, char c);
char					**ft_split_v2(char const *s);
unsigned long long		ft__atoi(const char *str);
char					**ft_split_vquote(char const *s);

#endif
