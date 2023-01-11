# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2023/01/11 19:41:51 by saaltone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem-editor

CC = gcc

FILES = app.c \
		editor.c \
		editor_menu.c \
		editor_ui.c \
		events.c \
		events_activate_interaction.c \
		events_inventory.c \
		events_keydown.c \
		events_keyup.c \
		events_menu.c \
		events_mouse.c \
		events_sector.c \
		export.c \
		image.c \
		import.c \
		interaction_checks.c \
		interaction_tools.c \
		interactions.c \
		linedraw.c \
		linedraw_utils.c \
		list_tools.c \
		lists.c \
		main.c \
		menu.c \
		menu_interaction_explanations.c \
		menu_interaction_explanations_extra.c \
		menu_interaction_info.c \
		menu_interaction_link_info.c \
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
		utils_sdl.c \
		import_interaction.c \
		import_sector.c

LIBFT = ../libft/libft.a
LIBLINEARALGEBRA = ../liblinearalgebra/liblinearalgebra.a
SDL2 = ../sdl/SDL2_build/lib/libSDL2.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

BUILD_DIR = ./compiled
OBJS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.o))
DEPS = $(patsubst %, $(BUILD_DIR)/%, $(FILES:.c=.d))

SDL_DIR = ../sdl
SDL_CONF = `../sdl/SDL2_build/bin/sdl2-config --cflags --libs`
SDL_V = SDL2-2.0.8

HEADERS = \
	-I ./includes \
	-I ../libft/includes \
	-I ../liblinearalgebra/includes \
	-I ../sdl/SDL2-2.0.8/include
	
FLAGS = -MMD -Wall -Wextra -Werror -O3 -g 

LIBLINKS = -L ../libft -L ../liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(SDL2) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(SDL_CONF) $(FLAGS) $(HEADERS) $(LIBLINKS)

# Create object files with (-MMD also creates dependency files)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

-include $(DEPS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	make -C ../libft

$(LIBLINEARALGEBRA):
	make -C ../liblinearalgebra

$(SDL2): 
	cd ../sdl/$(SDL_V)/build && ../configure --prefix=$(PWD)/sdl/SDL2_build/ && make install

.PHONY: all clean fclean re

clean-sdl:
	rm -rf sdl/$(SDL_V)/build/*
	touch sdl/$(SDL_V)/build/DontRemoveMe
	rm -rf sdl/SDL2_build/*
	touch sdl/SDL2_build/DontRemoveMe
	rm -f $(SDL2)

clean:
	make clean -C ../libft
	make clean -C ../liblinearalgebra
	/bin/rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C ../libft
	make fclean -C ../liblinearalgebra
	/bin/rm -f $(NAME)

re: fclean all
