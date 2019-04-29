# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/27 13:58:33 by ishaimou          #+#    #+#              #
#    Updated: 2019/04/28 13:22:53 by ishaimou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BGREEN = \033[1;32m
BCYAN = \033[1;36m
RESET = \033[0m

NAME = ft_ls
LIB_NAME = libft.a

LIB = -L./libft -lft

LIBFT_H = ./libft

FT_LS_H = ./includes

FLAGS = -Wall -Werror -Wextra

SRCS = main.c parse.c add_opts.c init.c \
	   list_files.c print_data.c print_lformat.c \
	   ft_cmp.c freef.c tools.c tools2.c print_modes.c
SRCS_DIR = $(addprefix srcs/, $(SRCS))

all: $(NAME)

$(NAME):
	@make -C ./libft
	@echo "$(BGREEN)$(LIB_NAME) has been created successfully.$(RESET)"
	@gcc -o $(NAME) $(FLAGS) $(SRCS_DIR) -I $(LIBFT_H) -I $(FT_LS_H) $(LIB)
	@echo "$(BGREEN)$(NAME) has been created successfully.$(RESET)"

clean:
	@make clean -C ./libft
	@echo "$(BCYAN)Object files has been cleaned successfully.$(RESET)"

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@echo "$(BCYAN)$(NAME) cleaned successfully.$(RESET)"

re: fclean all
