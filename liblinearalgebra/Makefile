# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 10:36:08 by saaltone          #+#    #+#              #
#    Updated: 2022/11/01 16:08:23 by htahvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=liblinearalgebra.a
CC = gcc
FLAGS=-Wall -Werror -Wextra -O3

FILES=ft_vector_length.c ft_vector_multiply_matrix.c ft_vector_perpendicular.c \
	ft_vector_resize.c ft_matrix_inverse.c ft_line_intersection.c \
	ft_vector_dotproduct.c ft_vector_crossproduct.c ft_line_resize.c \
	ft_line_side.c ft_vector_angle.c ft_line_intersection_through.c \
	ft_vector_sub.c ft_vector_add.c ft_lerp.c ft_vector_limit.c

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

OBJ_DIR = ./objs
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(FILES:.c=.o))

HEADERS = -I ./includes

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
