# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/12/02 15:17:54 by ssulkuma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem-editor

CC = gcc

FILES = app.c help_menu.c editor.c editor_ui.c editor_menu.c \
events_key.c events_mouse.c events.c export.c import.c player.c \
image.c main.c render.c render_extra.c render_text.c render_grid.c \
linedraw.c linedraw_utils.c lists.c menu_sector_info.c sector.c sector_tools.c \
sector_members.c sector_portal.c tex_icons.c tools.c utils_sdl.c utils.c \
menu_player_info.c menu_weapon_info.c  menu_inventory_info.c \
menu_object_info.c menu_interaction_info.c render_ui.c interactions.c \
objects.c events_menu.c

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

FRAMEWORKS = \
	-framework OpenGL -framework AppKit -framework OpenCl \

HEADERS = \
	-I ./includes \
	-I ../libft/includes \
	-I ../liblinearalgebra/includes \
	-I ../sdl/SDL2-2.0.8/include
	
FLAGS = -Wall -Wextra -Werror -O3 -g -fsanitize=address

LIBLINKS = -L ../libft -L ../liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm

all: $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(SDL2) $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $(NAME) $(SDL_CONF) $(FLAGS) $(HEADERS) $(FRAMEWORKS) $(LIBLINKS)

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
