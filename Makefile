NAME 	= 	cub3d

CC				= cc
CFLAGS 			= -Wall -Wextra -Werror -Wshadow -Wpedantic -g3

SRC_DIR = ./src
OBJ_DIR = ./obj

PARSER_DIR := $(SRC_DIR)/parser
ENGINE_DIR := $(SRC_DIR)/engine

SRCS 	:= 	src/main.c 						       \
			src/debugger.c						   \
			$(PARSER_DIR)/mlx_processing.c		   \
			$(PARSER_DIR)/parse_utils.c			   \
			$(PARSER_DIR)/parser.c				   \
			$(PARSER_DIR)/tokenize_input.c		   \
			$(PARSER_DIR)/utils.c				   \
			$(PARSER_DIR)/validate_identifiers.c   \
			$(PARSER_DIR)/validate_map.c		   \
			$(PARSER_DIR)/validate_map_surrounded.c\
			$(ENGINE_DIR)/render_it.c
			# $(ENGINE_DIR)/2dmap.c                  \
			# $(ENGINE_DIR)/dda_raycast.c            \
			# $(ENGINE_DIR)/drawgame.c               \
			# $(ENGINE_DIR)/hooks.c                  \
			# $(ENGINE_DIR)/hooks_determine_ra.c     \
			# $(ENGINE_DIR)/raycasting.c             \
			# $(ENGINE_DIR)/raycasting_utils.c       \
			# $(ENGINE_DIR)/utility.c

LIB				= ./libft/libft.a
LIBFT_LOC		= libft
LIBFT_LIB		= libft/libft.a
MLX_LOC			= MLX42
MLX_LIB			= MLX42/build/libmlx42.a

UNAME_S := $(shell uname -s)
MLX_FLAGS =
ifeq ($(UNAME_S), Darwin)  # macOS
    MLX_FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(UNAME_S), Linux)  # Linux
    MLX_FLAGS = -ldl -lglfw -pthread -lm
endif
HEADERS = -I include -I $(LIBFT_LOC)/include -I $(MLX_LOC)/include

OBJECTS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(MAKE) -C $(LIBFT_LOC)
	# @$(MAKE) -s -C $(MLX_LOC)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(MLX_LIB) $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(HEADERS) -c $(CFLAGS) -o $@ $<

clean:
	@$(MAKE) -s -C $(LIBFT_LOC) clean
	# @$(MAKE) -s -C $(MLX_LOC) clean
	@$ rm -rf $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_LOC) fclean

re: fclean all

.PHONY: all clean fclean re
