# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 14:35:22 by iassil            #+#    #+#              #
#    Updated: 2024/03/17 23:07:29 by aibn-che         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CC			+=	-g -Wall -Wextra -Werror
CC			+=	-fsanitize=address -fsanitize=undefined -O0
LINKER		=	-lreadline
RM			=	rm -f
NAME		=	minishell
HEADER_H	=	minishell.h
READLINEDIR = $(shell brew --prefix readline)

SRC 	=	t_utils/t_env_utils.c	t_utils/t_token_utils.c			t_utils/t_cont_utils.c		\
			t_utils/utils.c			execution/exec.c				utils.c						\
			signals.c				handle_path.c					minishell.c

SRC		+=	parsing/parsing.c		parsing/ft_tokenize.c			parsing/ft_check_syntax.c	\
			parsing/utils.c			parsing/ft_remove_quotes.c		parsing/ft_split_tokens.c

SRC		+=	parsing/ft_expand.c		builtin_ft/utils.c				builtin_ft/ft_echo.c		\
			builtin_ft/ft_exit.c	builtin_ft/ft_export.c			builtin_ft/ft_unset.c		\
			builtin_ft/ft_cd.c		builtin_ft/ft_env.c				builtin_ft/ft_pwd.c

SRC		+=	lib/ft_atoi.c			lib/ft_bzero.c					lib/ft_calloc.c				\
			lib/ft_isalnum.c		lib/ft_isalpha.c				lib/ft_isascii.c			\
			lib/ft_isdigit.c		lib/ft_isprint.c				lib/ft_memchr.c				\
			lib/ft_memcmp.c			lib/ft_memcpy.c					lib/ft_memmove.c			\
			lib/ft_memset.c			lib/ft_strchr.c					lib/ft_strdup.c				\
			lib/ft_strjoin.c		lib/ft_strlcat.c				lib/ft_strlcpy.c			\
			lib/ft_strlen.c			lib/ft_strncmp.c				lib/ft_strnstr.c			\
			lib/ft_strrchr.c		lib/ft_strtrim.c				lib/ft_substr.c				\
			lib/ft_tolower.c		lib/ft_toupper.c				lib/ft_itoa.c				\
			lib/ft_strmapi.c		lib/ft_striteri.c				lib/ft_putchar_fd.c			\
			lib/ft_putstr_fd.c		lib/ft_putendl_fd.c				lib/ft_putnbr_fd.c			\
			lib/ft_lstnew.c			lib/ft_lstadd_front.c			lib/ft_lstsize.c			\
			lib/ft_lstlast.c		lib/ft_lstadd_back.c			lib/ft_lstdelone.c			\
			lib/ft_lstclear.c		lib/ft_lstiter.c				lib/ft_lstmap.c				\
			lib/ft_split.c

SRC		+=	ft_printf/ft_printf.c		ft_printf/print_characters.c	ft_printf/print_hex.c	ft_printf/print_numbers.c   \
        	ft_printf/print_unsigned_int.c    	\

OBJ			=	$(SRC:.c=.o)

########### Goal Target
all: $(NAME)

########### Built Functions
%.o: %.c $(HEADER_H)
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