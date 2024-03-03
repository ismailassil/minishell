# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassil <iassil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 14:35:22 by iassil            #+#    #+#              #
#    Updated: 2024/03/03 15:27:58 by iassil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CC			+=	-Wall -Wextra -Werror
LINKER		=	-lreadline
RM			=	rm -f
NAME		=	minishell
HEADER_H	=	minishell.h

SRC 	=	lib/ft_atoi.c			lib/ft_bzero.c					lib/ft_calloc.c				\
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
			lib/ft_lstnew_bonus.c	lib/ft_lstadd_front_bonus.c		lib/ft_lstsize_bonus.c		\
			lib/ft_lstlast_bonus.c	lib/ft_lstadd_back_bonus.c		lib/ft_lstdelone_bonus.c	\
			lib/ft_lstclear_bonus.c	lib/ft_lstiter_bonus.c			lib/ft_lstmap_bonus.c		\
			lib/ft_split.c			signals.c						builtin_ft/ft_exit.c		\
			struct_utils.c			parsing.c						ft_tokenize.c				\
			ft_check_syntax.c		utils.c							minishell.c

OBJ			=	$(SRC:.c=.o)

########### Goal Target
all: $(NAME)

########### Built Functions
%.o: %.c $(HEADER_H)
	@$(CC) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compilation of the Objects files...$(RESET)"
	@$(CC) $(LINKER) $^ -o $@
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