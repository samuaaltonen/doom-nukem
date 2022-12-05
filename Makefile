# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/12/05 18:56:10 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

CC = gcc
PWD= $(shell pwd)

FILES = main.c \
		init.c \
		render_status.c \
		render_ui.c \
		render_text.c \
		button_function.c \
		error.c app.c \
		events_key.c \
		events_mouse.c \
		events_window.c \
		threads.c \
		image.c \
		player.c \
		player_init.c \
		player_view.c \
		events.c \
		audio.c \
		time.c \
		sector_draw_ceiling.c \
		sector_draw_floor.c \
		sector_draw_wall.c \
		sector_draw_wall_decor.c \
		sector_draw_partial.c \
		sector_draw_sky.c \
		sector_render.c \
		sector_visible_walls_order.c \
		sector_visible_walls.c \
		sector_wall_raycast.c \
		sector_wall_raycast_hit.c \
		sector_wall_raycast_decor.c \
		sector_wall_prepare.c \
		sector_wall_line.c \
		import.c \
		utils.c \
		utils_sdl.c \
		interaction_check.c \
		interaction_trigger.c \
		animation_create.c \
		animation_progress.c \
		init_texts.c \
		render_object.c

LIBFT = ./libft/libft.a
LIBLINEARALGEBRA = ./liblinearalgebra/liblinearalgebra.a
SDL2 = ./sdl/SDL2_build/lib/libSDL2.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

BUILD_DIR = ./compiled
OBJS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.o))
DEPS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.d))

SDL_DIR = ./sdl
SDL_CONF = `sdl/SDL2_build/bin/sdl2-config --cflags --libs`
SDL_V = SDL2-2.0.8
SDL_VNEW = SDL2-2.24.2

HEADERS = \
	-I ./includes \
	-I ./libft/includes \
	-I ./liblinearalgebra/includes \
	-I ./sdl/SDL2-2.0.8/include

FLAGS = -Wall -Wextra -Werror -flto -Ofast -g

LIBLINKS = -L ./libft -L ./liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(SDL2) $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $(NAME) $(SDL_CONF) $(FLAGS) $(HEADERS) $(LIBLINKS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) $(HEADERS) -MMD -c $< -o $@

-include $(DEPS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	make -C ./libft

$(LIBLINEARALGEBRA):
	make -C ./liblinearalgebra

$(SDL2): 
	cd sdl/$(SDL_V)/build && ../configure --prefix=$(PWD)/sdl/SDL2_build/ && make install

all_2.24.2: $(LIBFT) $(LIBLINEARALGEBRA) 2.24.2 $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $(NAME) $(SDL_CONF) $(FLAGS) $(HEADERS) $(LIBLINKS)


2.24.2:
	cd sdl/$(SDL_VNEW)/build && ../configure --prefix=$(PWD)/sdl/SDL2_build/ && make install

clean-sdl:
	rm -rf sdl/$(SDL_V)/build/*
	touch sdl/$(SDL_V)/build/DontRemoveMe
	rm -rf sdl/$(SDL_VNEW)/build/*
	touch sdl/$(SDL_VNEW)/build/DontRemoveMe
	rm -rf sdl/SDL2_build/*
	touch sdl/SDL2_build/DontRemoveMe
	rm -f $(SDL2)

clean:
	make clean -C ./libft
	make clean -C ./liblinearalgebra
	/bin/rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C ./libft
	make fclean -C ./liblinearalgebra
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean clean-sdl fclean re
