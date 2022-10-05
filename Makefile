# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 12:54:14 by htahvana          #+#    #+#              #
#    Updated: 2022/10/05 16:30:51 by dpalacio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

CC = gcc

MY_PATH = $(shell pwd)

FILES = main.c error.c conf.c app.c events.c events_key.c \
		events_mouse.c events_window.c graphics.c image.c \
		helper.c skybox.c player.c polygon_raycast.c \
		polygon_floor.c TESTDATA.c

LIBFT = ./libft/libft.a
LIBLINEARALGEBRA = ./liblinearalgebra/liblinearalgebra.a

SRC_DIR = ./srcs
SRCS := $(patsubst %, $(SRC_DIR)/%, $(FILES))

OBJ_DIR = ./objs
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(FILES:.c=.o))

SDL_DIR = ./sdl/
SDL_HEADERS = \
	-I$(SDL_DIR)include/SDL2 -D_THREAD_SAFE \
	-I$(SDL_DIR)SDL2_image.framework/Versions/A/Headers \
	-I$(SDL_DIR)SDL2_ttf.framework/Versions/A/Headers

SDL = $(SDL_DIR)build/build/.libs/

FRAMEWORKS = -F$(SDL_DIR) \
				-rpath $(SDL_DIR) \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2_ttf -framework SDL2_image

HEADERS = -I ./includes -I ./libft/includes -I ./liblinearalgebra/includes \
		-I /usr/local/include/SDL2 $(SDL_HEADERS)

FLAGS = -Wall -Wextra -Werror -flto -Ofast

LIBLINKS = -L ./libft -L ./liblinearalgebra -L/usr/local/lib \
		-llinearalgebra -lft -lm -L$(SDL) -lSDL2

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: sdl_install $(NAME)

$(NAME): $(LIBFT) $(LIBLINEARALGEBRA) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(HEADERS) $(FRAMEWORKS) $(LIBLINKS)
	@echo "\n$(NAME): $(GREEN)Created object files.$(RESET)"
	@echo "$(NAME): $(GREEN)Created $(NAME) executable.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GREEN)Created obj/ directory.$(RESET)"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Compiling Libft...$(RESET)"
	@make -C ./libft

$(LIBLINEARALGEBRA):
	@echo "$(NAME): $(GREEN)Compiling Linear Algebra Library...$(RESET)"
	@make -C ./liblinearalgebra

sdl_install:
	@if [ -d "$(SDL_DIR)build/" ];\
	then\
		echo "$(NAME): $(YELLOW)SDL2 already exists.$(RESET)";\
	else\
		mkdir -p $(SDL_DIR)build/;\
		echo "$(NAME): $(GREEN)Configuring SDL2...$(RESET)";\
		cd $(SDL_DIR)build/; ../configure --prefix $(MYPATH)/sdl/build;\
		cd $(MY_PATH);\
		bash sdl_path.sh;\
		echo "$(NAME): $(GREEN)Installing SDL2...$(RESET)";\
		$(MAKE) -sC $(SDL_DIR)build/ install;\
		echo "$(NAME): $(GREEN)SDL2  was installed.$(RESET)";\
	fi;

sdl_uninstall:
	@rm -fr $(SDL_DIR)build/
	@echo "$(NAME): $(YELLOW)SDL2 was uninstalled.$(RESET)"

.PHONY: all clean fclean re

clean:
	@make clean -C ./libft
	@make clean -C ./liblinearalgebra
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft
	make fclean -C ./liblinearalgebra

re: fclean all
