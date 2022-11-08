# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/11/08 16:25:00 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem-editor

CC = gcc

FILES = app.c help_menu.c editor.c editor_ui.c editor_menu.c \
events_key.c events_mouse.c events.c export.c import.c player.c \
image.c main.c render.c render_extra.c render_text.c render_grid.c \
linedraw.c linedraw_utils.c lists.c sector.c sector_tools.c \
sector_members.c sector_portal.c tex_icons.c tools.c utils_sdl.c utils.c 

LIBFT = ../libft/libft.a
LIBLINEARALGEBRA = ../liblinearalgebra/liblinearalgebra.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

BUILD_DIR = ./compiled
OBJS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.o))
DEPS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.d))

SDL_DIR = ../sdl/
SDL_HEADERS = \
	-I$(SDL_DIR)SDL2.framework/Versions/A/Headers \

FRAMEWORKS = -F$(SDL_DIR) \
				-rpath $(SDL_DIR) \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2

HEADERS = -I ./includes -I ../libft/includes -I ../liblinearalgebra/includes \
		-I /usr/local/include/SDL2 $(SDL_HEADERS)

FLAGS = -Wall -Wextra -Werror -O3 -g -fsanitize=address

LIBLINKS = -L ../libft -L ../liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(HEADERS) $(FRAMEWORKS) $(LIBLINKS)

# Create object files with (-MMD also creates dependency files)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) $(HEADERS) -MMD -c $< -o $@

-include $(DEPS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	make -C ../libft

$(LIBLINEARALGEBRA):
	make -C ../liblinearalgebra

.PHONY: all clean fclean re

clean:
	make clean -C ../libft
	make clean -C ../liblinearalgebra
	/bin/rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C ../libft
	make fclean -C ../liblinearalgebra
	/bin/rm -f $(NAME)

re: fclean all
