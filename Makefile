# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassil <iassil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 14:35:22 by iassil            #+#    #+#              #
#    Updated: 2024/03/20 14:01:50 by iassil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
CC			+=	-Wall -Wextra -Werror
READLINEDIR	=	$(shell brew --prefix readline)
CC			+=	-fsanitize=address -fsanitize=undefined -g
LINKER		=	-lreadline
RM			=	rm -f
NAME		=	minishell
HEADER_H	=	minishell.h			lib/get_next_line/get_next_line.h

MAIN_FILES	=	minishell.c			signals.c				s_utils.c

UTILS_FILES =	t_env_utils.c		t_token_utils.c			t_cont_utils.c		\
				t_utils.c

EXEC_FILES	=	exec.c				proc_utils.c			exec_builtin.c		\
				here_doc.c			fill_container.c		mutli_cmds.c		\
				e_utils.c			exec_builtin_utils.c

PARS_FILES	=	parsing.c			ft_tokenize.c			ft_check_syntax.c	\
				ft_expand.c			ft_remove_quotes.c		ft_split_tokens.c	\
				p_utils.c

BUILT_FILES	=	ft_echo.c			ft_env.c				ft_pwd.c			\
				ft_exit.c			ft_export.c				ft_unset.c			\
				ft_cd.c				b_utils.c

LIB_FILES	=	ft_atoi.c			ft_bzero.c				ft_calloc.c			\
				ft_isalnum.c		ft_isalpha.c			ft_isascii.c		\
				ft_isdigit.c		ft_isprint.c			ft_memchr.c			\
				ft_memcmp.c			ft_memcpy.c				ft_memmove.c		\
				ft_memset.c			ft_strchr.c				ft_strdup.c			\
				ft_strjoin.c		ft_strlcat.c			ft_strlcpy.c		\
				ft_strlen.c			ft_strncmp.c			ft_strnstr.c		\
				ft_strrchr.c		ft_strtrim.c			ft_substr.c			\
				ft_tolower.c		ft_toupper.c			ft_itoa.c			\
				ft_strmapi.c		ft_striteri.c			ft_putchar_fd.c		\
				ft_putstr_fd.c		ft_putendl_fd.c			ft_putnbr_fd.c		\
				ft_lstnew.c			ft_lstadd_front.c		ft_lstsize.c		\
				ft_lstlast.c		ft_lstadd_back.c		ft_lstdelone.c		\
				ft_lstclear.c		ft_lstiter.c			ft_lstmap.c			\
				ft_split.c

MAIN_SRC	=	$(addprefix src/,$(MAIN_FILES))
UTILS_SRC	=	$(addprefix t_utils/,$(UTILS_FILES))
EXEC_SRC	=	$(addprefix execution/,$(EXEC_FILES))
PARS_SRC	=	$(addprefix parsing/,$(PARS_FILES))
BUILT_SRC	=	$(addprefix builtin_ft/,$(BUILT_FILES))
LIB_SRC		=	$(addprefix lib/,$(LIB_FILES))

MAIN_OBJ	=	$(addprefix _object_files/,$(MAIN_SRC:.c=.o))
UTILS_OBJ	=	$(addprefix _object_files/,$(UTILS_SRC:.c=.o))
EXEC_OBJ	=	$(addprefix _object_files/,$(EXEC_SRC:.c=.o))
PARS_OBJ	=	$(addprefix _object_files/,$(PARS_SRC:.c=.o))
BUILT_OBJ	=	$(addprefix _object_files/,$(BUILT_SRC:.c=.o))
LIB_OBJ		=	$(addprefix _object_files/,$(LIB_SRC:.c=.o))

OBJ 		=	$(MAIN_OBJ) $(EXEC_OBJ) $(GNL_OBJ) $(UTILS_OBJ)	\
				$(PARS_OBJ) $(BUILT_OBJ) $(LIB_OBJ)

########### Goal Target
all: $(NAME)

########### Built Functions
_object_files/builtin_ft/%.o: builtin_ft/%.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

_object_files/execution/%.o: execution/%.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

_object_files/lib/%.o: lib/%.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

_object_files/parsing/%.o: parsing/%.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

_object_files/t_utils/%.o: t_utils/%.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

_object_files/src/%.o: src/%.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compilation of the Objects files...$(RESET)"
	@$(CC) $(LINKER) $^ -o $@ -L$(READLINEDIR)/lib
	@echo "$(GREEN)[====Executable file Compiled Successfully!====]$(RESET)"

clean:
	@echo "$(YELLOW)Removing Object files...$(RESET)"
	@$(RM) $(OBJ)
	@echo "$(GREEN)[====Object files removed successfully!====]$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing Executable...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)[====Executable files removed successfully!====]$(RESET)"

re: fclean all

.PHONY: all fclean clean re

########## DFine ANSI escape codes for colors
GREEN=	\033[32m
YELLOW=	\033[0;33m
RESET=	\033[0m		# No Color