# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2023/01/12 18:06:57 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

CC = gcc
PWD= $(shell pwd)

FILES = animation_create.c \
		animation_progress.c \
		app.c \
		audio.c \
		button_function.c \
		enemy_move.c \
		enemy_states.c \
		error.c \
		events.c \
		events_key.c \
		events_mouse.c \
		events_window.c \
		image.c \
		import.c \
		init.c \
		interaction_check.c \
		interaction_trigger.c \
		main.c \
		object_collision.c \
		player_collision.c \
		player_collision_portal.c \
		player_collision_sector.c \
		player_collision_slope.c \
		player_collision_wall.c \
		player_control.c \
		player_effects.c \
		player_elevate.c \
		player_init.c \
		player_move.c \
		player_view.c \
		projectiles.c \
		render_object.c \
		render_status.c \
		render_text.c \
		render_ui.c \
		sector_draw_ceiling.c \
		sector_draw_floor.c \
		sector_draw_partial.c \
		sector_draw_sky.c \
		sector_draw_wall.c \
		sector_draw_wall_decor.c \
		sector_elevation.c \
		sector_render.c \
		sector_wall_line.c \
		sector_wall_prepare.c \
		sector_wall_raycast.c \
		sector_wall_raycast_decor.c \
		sector_wall_raycast_hit.c \
		sector_wallstack.c \
		sector_wallstack_order.c \
		sector_wallstack_visible.c \
		textmodal.c \
		threads.c \
		time.c \
		utils.c \
		utils_bmp.c \
		utils_color.c \
		utils_sdl.c \
		import_loading.c \
		rle_utils.c \
		rle_uncompress.c \
		render_hand.c \
		import_sector.c \
		import_assets.c \
		import_assets_surface.c \
		import_assets_wav.c \
		import_assets_text.c \
		level_validation.c \
		level_validation_sector.c \
		level_validation_assets.c \
		level_validation_interaction.c

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

FLAGS = -MMD -Wall -Wextra -Werror -flto -Ofast -g

LIBLINKS = -L ./libft -L ./liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(SDL2) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(SDL_CONF) $(FLAGS) $(HEADERS) $(LIBLINKS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(HEADERS) $(FLAGS) -c $< -o $@

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

fclean: clean clean-sdl
	make fclean -C ./libft
	make fclean -C ./liblinearalgebra
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean clean-sdl fclean re
