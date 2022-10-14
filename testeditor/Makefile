# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/10/14 16:29:37 by htahvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem-editor

CC = gcc

FILES = editor.c events_key.c app.c events.c image.c main.c render.c \
 linedraw.c lists.c export.c import.c tools.c TESTDATA.c

LIBFT = ../libft/libft.a
LIBLINEARALGEBRA = ../liblinearalgebra/liblinearalgebra.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

OBJ_DIR = ./objs
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(FILES:.c=.o))

SDL_DIR = ../sdl/
SDL_HEADERS = \
	-I$(SDL_DIR)SDL2.framework/Versions/A/Headers \
	-I$(SDL_DIR)SDL2_image.framework/Versions/A/Headers \
	-I$(SDL_DIR)SDL2_ttf.framework/Versions/A/Headers \

FRAMEWORKS = -F$(SDL_DIR) \
				-rpath $(SDL_DIR) \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image

HEADERS = -I ./includes -I ../libft/includes -I ../liblinearalgebra/includes \
		-I /usr/local/include/SDL2 $(SDL_HEADERS)

FLAGS = -Wall -Wextra -Werror -O3 -g -fsanitize=address

LIBLINKS = -L ../libft -L ../liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(HEADERS) $(FRAMEWORKS) $(LIBLINKS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C ../libft

$(LIBLINEARALGEBRA):
	make -C ../liblinearalgebra

.PHONY: all clean fclean re

clean:
	make clean -C ../libft
	make clean -C ../liblinearalgebra
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C ../libft
	make fclean -C ../liblinearalgebra
	/bin/rm -f $(NAME)

re: fclean all
