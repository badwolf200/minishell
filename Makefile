# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/02 14:55:32 by rkowalsk          #+#    #+#              #
#    Updated: 2021/06/07 15:02:15 by rkowalsk         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
	srcs/minishell.c \
	srcs/useful/useful.c \
	srcs/useful/useful_returns.c \
	srcs/useful/useful_escape_char.c \
	srcs/useful/useful_split_returns.c \
	srcs/init_stuff.c \
	srcs/commands/cmd_echo.c \
	srcs/commands/cmd_env_pwd_cd_setvar.c \
	srcs/commands/cmd_export.c \
	srcs/commands/execve.c \
	srcs/commands/proceed_cmd.c \
	srcs/commands/env_list_to_tab.c \
	srcs/parsing/line_parsing.c \
	srcs/parsing/pars_semicolons.c \
	srcs/parsing/pars_spaces.c \
	srcs/parsing/pars_pipes.c \
	srcs/parsing/fork.c \
	srcs/parsing/variables.c \
	srcs/parsing/redirections.c \
	srcs/parsing/redirections_dup_name.c \
	srcs/parsing/redirections_open_inout.c \
	srcs/parsing/get_line.c \
	srcs/parsing/get_line2.c \
	srcs/parsing/arrow_keys.c \
	srcs/environment_list/env_list.c \
	srcs/environment_list/env_list_2.c \
	srcs/history_list/history_struct.c

OBJS = ${SRCS:.c=.o}

INCLUDES = includes/minishell.h \
		   includes/libft.h

LIBFT = libft/libft.a

$(NAME): $(OBJS) $(LIBFT)
	clang -o $(NAME) $(OBJS) $(LIBFT) -ltermcap 

$(OBJS): %.o: %.c $(INCLUDES)
	clang -Wall -Wextra -Werror -Iincludes -c $< -o $@

$(LIBFT): 
	$(MAKE) -C libft all

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all