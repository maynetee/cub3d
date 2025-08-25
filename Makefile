NAME = cub3d

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = lib/libft
MLX_PATH = lib/minilibx-linux

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC_FILES = \
$(SRC_DIR)/core/game_loop.c \
$(SRC_DIR)/core/main.c \
$(SRC_DIR)/graphics/mlx_init.c \
$(SRC_DIR)/graphics/minimap.c \
$(SRC_DIR)/graphics/minimap_utils.c \
$(SRC_DIR)/graphics/render_utils.c \
$(SRC_DIR)/graphics/render_wall.c \
$(SRC_DIR)/graphics/texture_load.c \
$(SRC_DIR)/input/input_keys.c \
$(SRC_DIR)/parser/bridge_to_scene.c \
$(SRC_DIR)/parser/error.c \
$(SRC_DIR)/parser/flood_fill.c \
$(SRC_DIR)/parser/init.c \
$(SRC_DIR)/parser/line_validation.c \
$(SRC_DIR)/parser/map_collect.c \
$(SRC_DIR)/parser/map_collect_utils.c \
$(SRC_DIR)/parser/map_enclosure.c \
$(SRC_DIR)/parser/map_utils.c \
$(SRC_DIR)/parser/map_validate.c \
$(SRC_DIR)/parser/parse_color_utils.c \
$(SRC_DIR)/parser/parse_colors.c \
$(SRC_DIR)/parser/parse_cub.c \
$(SRC_DIR)/parser/parse_cub_utils.c \
$(SRC_DIR)/parser/parse_elements.c \
$(SRC_DIR)/parser/player.c \
$(SRC_DIR)/parser/string_split.c \
$(SRC_DIR)/parser/string_token_utils.c \
$(SRC_DIR)/parser/string_utils.c \
$(SRC_DIR)/parser/utils.c \
$(SRC_DIR)/player/player_init.c \
$(SRC_DIR)/player/player_move.c \
$(SRC_DIR)/raycasting/raycast_dda.c \
$(SRC_DIR)/raycasting/raycast_render.c \
$(SRC_DIR)/utils/cleanup_mem.c \
$(SRC_DIR)/utils/file_utils.c \
$(SRC_DIR)/utils/find_player_in_map.c \
$(SRC_DIR)/utils/utils.c \
$(SRC_DIR)/utils/utils_extra.c

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
	MLX_FLAGS = -lX11 -lXext -lm
endif

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	@$(MAKE) -C $(MLX_PATH)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx $(MLX_FLAGS)
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes -I$(MLX_PATH) -c -o $@ $<
	@echo "$(NAME): $(GREEN)$@ was created$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "$(NAME): $(GREEN)$(LIBFT) was created$(RESET)"

$(MLX):
	@$(MAKE) -C $(MLX_PATH)
	@echo "$(NAME): $(GREEN)$(MLX) was created$(RESET)"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
