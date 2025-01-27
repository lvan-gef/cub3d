NAME := cub3D

# Compiler and flags
CC        := cc
CFLAGS    := -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -Wdouble-promotion
DEBUGFLAG := -g3
ASAN      := -fsanitize=address -fno-omit-frame-pointer
DEPSFLAGS := -MMD -MP

# Directories
SRC_DIR   := src
ENG_DIR   := $(SRC_DIR)/engine
PAR_DIR   := $(SRC_DIR)/parser
OBJ_DIR   := obj
DEP_DIR   := $(OBJ_DIR)

# Source files organization
ENGINE_SRC := buffer.c dda_calc.c render.c init_mlx.c textures.c hooks.c
PARSER_SRC := parser.c parse_utils.c validate_identifiers.c validate_ident_utils.c \
              validate_map.c validate_map_utils.c validate_map_surrounded.c \
              tokenize_input.c tokenize_utils.c
MAIN_SRC   := main.c cub_free.c

# Construct full paths
SRCS := $(addprefix $(SRC_DIR)/, $(MAIN_SRC)) \
        $(addprefix $(ENG_DIR)/, $(ENGINE_SRC)) \
        $(addprefix $(PAR_DIR)/, $(PARSER_SRC))

# Objects and dependencies
OBJECTS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

# Libraries
LIBFT_DIR  := libft
LIBFT      := $(LIBFT_DIR)/libft.a
LIBMLX_DIR := MLX42
LIBMLX     := $(LIBMLX_DIR)/build/libmlx42.a

# OS-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(UNAME_S), Linux)
    MLX_FLAGS := -ldl -lglfw -pthread -lm
else
    $(error Unsupported operating system: $(UNAME_S))
endif

# Include paths
HEADERS := -I include -I $(LIBFT_DIR)/include -I $(LIBMLX_DIR)/include

# Colors for help message
BLUE := \033[36m
MARGENTA := \033[35m
NC := \033[0m

# Build rules
.PHONY: all
all: $(NAME)  ## Build release version (default)

.PHONY: debug
debug: CFLAGS += $(DEBUGFLAG) $(ASAN)
debug: $(NAME)  ## Build the debug version with ASAN

.PHONY: clean
clean:  ## Clean object files
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned object files"

.PHONY: fclean
fclean: clean  ## Clean object, bin and MLX files
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(LIBMLX_DIR)
	@rm -f $(NAME)
	@echo "Cleaned everything"

.PHONY: re
re: fclean all  ## Clean all and recompile

.PHONY: help
help:  ## Get help
	@echo -e 'Usage: make ${BLUE}<target>${NC}'
	@echo -e 'Available targets:'
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "  ${BLUE}%-15s${NC} %s\n", $$1, $$2}' $(MAKEFILE_LIST)

# Main build
$(NAME): $(LIBFT) $(LIBMLX) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBMLX) $(LIBFT) $(MLX_FLAGS) -o $@
	@echo "Build complete: $(NAME)"

# Pattern rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPSFLAGS) $(HEADERS) -c $< -o $@

# Create directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/engine $(OBJ_DIR)/parser

# Library builds
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	@if [ ! -d "$(LIBMLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX_DIR) && \
		cd $(LIBMLX_DIR) && \
		git checkout v2.3.3 && \
		cmake -B build && \
		cmake --build build -j4; \
	fi

-include $(DEPS)
