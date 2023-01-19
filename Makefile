# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2023/01/19 18:52:50 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
EDITOR_NAME = level-editor

CC = gcc
PWD= $(shell pwd)

FILES = animation_create.c \
		animation_progress.c \
		app.c \
		audio.c \
		bullet_collisions.c \
		bullet_object_collisions.c \
		bullet_wall_collisions.c \
		bullets.c \
		button_function.c \
		enemy_avoidance.c \
		enemy_move.c \
		enemy_states.c \
		enemy_utils.c \
		error.c \
		events.c \
		events_key.c \
		events_mouse.c \
		events_window.c \
		image.c \
		import.c \
		import_assets.c \
		import_assets_surface.c \
		import_assets_text.c \
		import_assets_wav.c \
		import_async.c \
		import_interaction.c \
		import_object.c \
		import_player.c \
		import_sector.c \
		init.c \
		interaction_check.c \
		interaction_trigger.c \
		level_validation.c \
		level_validation_assets.c \
		level_validation_interaction.c \
		level_validation_object.c \
		level_validation_player.c \
		level_validation_sector.c \
		main.c \
		object_collision.c \
		object_multithreading.c \
		object_render_init.c \
		object_render_utils.c \
		object_render_work.c \
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
		render_hand.c \
		render_object.c \
		render_status_game.c \
		render_status_gameover.c \
		render_status_mainmenu.c \
		render_status_options.c \
		render_status_pausemenu.c \
		render_status_titlescreen.c \
		render_text.c \
		render_ui.c \
		rle_uncompress.c \
		rle_utils.c \
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
		utils_color.c \
		utils_sdl.c

EDITOR_FILES = app.c \
		editor.c \
		editor_menu.c \
		editor_ui.c \
		events.c \
		events_activate_interaction.c \
		events_dispatch.c \
		events_inventory.c \
		events_keydown.c \
		events_keyup.c \
		events_menu.c \
		events_mouse.c \
		events_mouse_track.c \
		events_mouse_wheel.c \
		events_sector.c \
		export.c \
		export_assets_surface.c \
		export_assets_text.c \
		export_assets_wav.c \
		export_async.c \
		export_interaction.c \
		export_object.c \
		export_player.c \
		export_sector.c \
		image.c \
		import.c \
		import_async.c \
		import_interaction.c \
		import_object.c \
		import_player.c \
		import_sector.c \
		interaction_checks.c \
		interaction_tools.c \
		interactions.c \
		level_validation_sector.c \
		linedraw.c \
		linedraw_utils.c \
		list_tools.c \
		lists.c \
		loading_screen.c \
		main.c \
		menu.c \
		menu_gravity.c \
		menu_interaction_explanations.c \
		menu_interaction_explanations_extra.c \
		menu_interaction_info.c \
		menu_interaction_link_info.c \
		menu_interaction_tools.c \
		menu_inventory_info.c \
		menu_object_info.c \
		menu_player_info.c \
		menu_sector_info.c \
		menu_tools.c \
		menu_wall_info.c \
		menu_weapon_info.c \
		object_tools.c \
		objects.c \
		player.c \
		render.c \
		render_extra.c \
		render_grid.c \
		render_text.c \
		render_ui.c \
		rle_compress.c \
		rle_uncompress.c \
		rle_utils.c \
		sector.c \
		sector_interactions.c \
		sector_members.c \
		sector_portal.c \
		sector_tools.c \
		tex_icons.c \
		tools.c \
		triangle.c \
		utils.c \
		utils_bmp.c \
		utils_sdl.c

LIBFT = ./libft/libft.a
LIBLINEARALGEBRA = ./liblinearalgebra/liblinearalgebra.a
SDL2 = ./sdl/SDL2_build/lib/libSDL2.a

SRCS_DIR = ./srcs
SRCS := $(patsubst %, $(SRCS_DIR)/%, $(FILES))

EDITOR_SRCS_DIR = ./editor_srcs
EDITOR_SRCS := $(patsubst %, $(EDITOR_SRCS_DIR)/%, $(EDITOR_FILES))

BUILD_DIR = ./compiled
OBJS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.o))
DEPS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.d))

EDITOR_BUILD_DIR = ./editor_compiled
EDITOR_OBJS = $(patsubst %, $(EDITOR_BUILD_DIR)/%, $(EDITOR_FILES:.c=.o))
EDITOR_DEPS = $(patsubst %, $(EDITOR_BUILD_DIR)/%, $(EDITOR_FILES:.c=.d))

SDL_DIR = ./sdl
SDL_CONF = `sdl/SDL2_build/bin/sdl2-config --cflags --libs`
SDL_V = SDL2-2.0.8
SDL_VNEW = SDL2-2.24.2

HEADERS = \
	-I ./includes \
	-I ./libft/includes \
	-I ./liblinearalgebra/includes \
	-I ./sdl/SDL2-2.0.8/include

EDITOR_HEADERS = \
	-I ./editor_includes \
	-I ./libft/includes \
	-I ./liblinearalgebra/includes \
	-I ./sdl/SDL2-2.0.8/include

FLAGS = -MMD -Wall -Wextra -Werror -flto -Ofast -g

LIBLINKS = -L ./libft -L ./liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME) $(EDITOR_NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(SDL2) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(SDL_CONF) $(FLAGS) $(HEADERS) $(LIBLINKS)

$(EDITOR_NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(SDL2) $(EDITOR_OBJS)
	$(CC) $(EDITOR_OBJS) -o $(EDITOR_NAME) $(SDL_CONF) $(FLAGS) $(EDITOR_HEADERS) $(LIBLINKS)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(HEADERS) $(FLAGS) -c $< -o $@

-include $(DEPS)

$(EDITOR_BUILD_DIR)/%.o: $(EDITOR_SRCS_DIR)/%.c | $(EDITOR_BUILD_DIR)
	$(CC) $(EDITOR_HEADERS) $(FLAGS) -c $< -o $@

-include $(EDITOR_DEPS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EDITOR_BUILD_DIR):
	mkdir -p $(EDITOR_BUILD_DIR)

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
	/bin/rm -rf $(EDITOR_BUILD_DIR)

fclean: clean clean-sdl
	make fclean -C ./libft
	make fclean -C ./liblinearalgebra
	/bin/rm -f $(NAME)
	/bin/rm -f $(EDITOR_NAME)

re: fclean all

.PHONY: all clean clean-sdl fclean re
