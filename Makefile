NAME = cub3d

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = lib/libft
MLX_PATH = lib/minilibx
GNL_PATH = lib/gnl

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a
GNL = $(GNL_PATH)/libgnl.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
	MLX_FLAGS = -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX) $(GNL)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_PATH) -lft -L$(GNL_PATH) -lgnl -L$(MLX_PATH) -lmlx $(MLX_FLAGS)
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_PATH) -I$(GNL_PATH) -I$(MLX_PATH) -c -o $@ $<
	@echo "$(NAME): $(GREEN)$@ was created$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "$(NAME): $(GREEN)$(LIBFT) was created$(RESET)"

$(GNL):
	@$(MAKE) -C $(GNL_PATH)
	@echo "$(NAME): $(GREEN)$(GNL) was created$(RESET)"

$(MLX):
	@$(MAKE) -C $(MLX_PATH)
	@echo "$(NAME): $(GREEN)$(MLX) was created$(RESET)"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@$(MAKE) -C $(GNL_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) -C $(GNL_PATH) fclean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
