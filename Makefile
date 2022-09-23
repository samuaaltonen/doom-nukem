# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/09/23 21:32:31 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

CC = gcc

FILES = main.c error.c conf.c app.c events.c events_key.c \
		events_mouse.c events_window.c graphics.c image.c \
		helper.c skybox.c floor.c player.c polygon_raycast.c

LIBFT = ./libft/libft.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

OBJ_DIR = ./objs
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(FILES:.c=.o))

HEADERS = -I ./includes -I ./libft/includes -I /usr/local/include/SDL2 -lm -lSDL2 -lSDL2_image

FLAGS = -Wall -Wextra -Werror -O3 -g

LIBFTLINKS = -I ./libft/includes -L ./libft -lft

all: $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(LIBFTLINKS) $(HEADERS) \
	-L/usr/local/lib

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C ./libft

.PHONY: all clean fclean re

clean:
	make clean -C ./libft
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)

re: fclean all
