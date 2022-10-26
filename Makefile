# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/10/26 15:35:05 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

CC = gcc

FILES = main.c init.c render.c buttons.c error.c conf.c app.c  \
		events_key.c events_mouse.c events_window.c graphics.c image.c \
		helper.c skybox.c player.c events.c \
		sector_draw_ceiling.c sector_draw_floor.c sector_draw_wall.c \
		sector_render.c sector_visible_walls_order.c sector_visible_walls.c \
		sector_wall_raycast.c sector_wall_prepare.c sector_wall_line.c \
		sector_draw_partial.c render_text.c ui.c import.c utils.c utils_sdl.c

LIBFT = ./libft/libft.a
LIBLINEARALGEBRA = ./liblinearalgebra/liblinearalgebra.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

BUILD_DIR = ./build
OBJS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.o))
DEPS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.d))

SDL_DIR = ./sdl/
SDL_HEADERS = \
	-I$(SDL_DIR)SDL2.framework/Versions/A/Headers \

FRAMEWORKS = -F$(SDL_DIR) \
				-rpath $(SDL_DIR) \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2

HEADERS = -I ./includes -I ./libft/includes -I ./liblinearalgebra/includes \
		-I /usr/local/include/SDL2 $(SDL_HEADERS)

FLAGS = -Wall -Wextra -Werror -flto -Ofast -g

LIBLINKS = -L ./libft -L ./liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(HEADERS) $(FRAMEWORKS) $(LIBLINKS)

# Create object files with (-MMD also creates dependency files)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) $(HEADERS) -MMD -c $< -o $@

-include $(DEPS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	make -C ./libft

$(LIBLINEARALGEBRA):
	make -C ./liblinearalgebra

.PHONY: all clean fclean re

clean:
	make clean -C ./libft
	make clean -C ./liblinearalgebra
	/bin/rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C ./libft
	make fclean -C ./liblinearalgebra
	/bin/rm -f $(NAME)

re: fclean all
