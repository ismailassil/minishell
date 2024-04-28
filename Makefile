# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassil <iassil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 14:35:22 by iassil            #+#    #+#              #
#    Updated: 2024/04/28 19:14:06 by iassil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CC			+=	-Wall -Wextra -Werror
READLINEDIR	=	$(shell brew --prefix readline)
# CC			+=	-fsanitize=address -fsanitize=undefined -g
LINKER		=	-lreadline
RM			=	rm -f
NAME		=	minishell
HEADER_H	=	minishell.h

SRC_FILES	=	minishell.c			signals.c				src_utils_v1.c		\
				src_utils_v2.c

UTILS_FILES =	t_env_utils.c		t_token_utils.c			t_cont_utils.c		\
				ft_sort_list.c		t_utils_v1.c			t_utils_v2.c		\

EXEC_FILES	=	execution.c				process_utils_v1.c		execute_builtin.c		\
				here_doc.c				fill_container.c		mutli_cmds.c			\
				free_fun.c				here_doc_utils_v1.c		here_doc_utils_v2.c		\
				execution_utils_v1.c	execution_utils_v2.c	execution_utils_v3.c	\
				process_utils_v2.c		process_utils_v3.c		ft_index_files.c		\
				execution_utils_v4.c	fill_container_utils.c	execute_wildcards.c		\
				here_doc_utils_v3.c		ft_open_files.c			ft_check_file_name.c	\
				ft_check_file_name_utils.c	execute_builtin_utils_v2.c					\
				ft_split_after_expanding.c	execute_builtin_utils_v1.c

PARS_FILES	=	parsing.c			ft_tokenize.c			ft_check_syntax.c	\
				ft_expand.c			ft_remove_quotes.c		ft_split_tokens.c	\
				parse_utils_v1.c	parse_utils_v2.c		wildcards.c			\
				ft_expand_utils_v1.c	ft_expand_utils_v2.c   ft_expand_utils.c

BUILT_FILES	=	ft_echo.c			ft_env.c				ft_pwd.c			\
				ft_exit.c			ft_export.c				ft_unset.c			\
				ft_cd.c				builtin_utils_v1.c		builtin_utils_v2.c	\
				buitlin_utils_v3.c

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
				ft_split.c			ft_split_v2.c			ft_split_v3.c

SRC_SRC		=	$(addprefix src/,$(SRC_FILES))
UTILS_SRC	=	$(addprefix t_utils/,$(UTILS_FILES))
EXEC_SRC	=	$(addprefix execution/,$(EXEC_FILES))
PARS_SRC	=	$(addprefix parsing/,$(PARS_FILES))
BUILT_SRC	=	$(addprefix builtin_ft/,$(BUILT_FILES))
LIB_SRC		=	$(addprefix lib/,$(LIB_FILES))

SRC_OBJ		=	$(addprefix _object_files/,$(SRC_SRC:.c=.o))
UTILS_OBJ	=	$(addprefix _object_files/,$(UTILS_SRC:.c=.o))
EXEC_OBJ	=	$(addprefix _object_files/,$(EXEC_SRC:.c=.o))
PARS_OBJ	=	$(addprefix _object_files/,$(PARS_SRC:.c=.o))
BUILT_OBJ	=	$(addprefix _object_files/,$(BUILT_SRC:.c=.o))
LIB_OBJ		=	$(addprefix _object_files/,$(LIB_SRC:.c=.o))

OBJ 		=	$(SRC_OBJ) $(EXEC_OBJ) $(UTILS_OBJ)	\
				$(PARS_OBJ) $(BUILT_OBJ) $(LIB_OBJ)

########### Goal Target
all: $(NAME)

# Define a pattern rule for compiling object files
_object_files/%.o: %.c $(HEADER_H)
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

$(NAME): $(OBJ)
	@echo "$(YELLOW)[ ~ ] Compilation of the Objects files...$(RESET)"
	@$(CC) $(LINKER) $^ -o $@ -L$(READLINEDIR)/lib
	@echo "$(GREEN)[ ✓ ] Executable file Compiled Successfully!$(RESET)"

clean:
	@echo "$(YELLOW)[ ~ ] Removing Object files $(RESET)"
	@$(RM) $(OBJ)
	@$(RM) -rf _object_files
	@echo "$(GREEN)[ ✓ ] Object files removed successfully!$(RESET)"
	
fclean: clean
	@echo "$(YELLOW)[ ~ ] Removing Executable...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)[ ✓ ] Executable files removed successfully!$(RESET)"

re: fclean all

.PHONY: all fclean clean re

########## DFine ANSI escape codes for colors
GREEN=	\033[1;32m
YELLOW=	\033[33m
RESET=	\033[0m		# No Color