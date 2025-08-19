NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I includes -I Libft/includes

LIBFT_DIR   = Libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
       srcs/parser/parse_colors.c \
       srcs/parser/parse_color_utils.c \
       srcs/parser/parse_cub.c \
       srcs/parser/parse_cub_utils.c \
       srcs/parser/line_validation.c \
       srcs/parser/parse_elements.c \
       srcs/parser/map_collect.c \
       srcs/parser/map_collect_utils.c \
       srcs/parser/map_validate.c \
       srcs/parser/map_enclosure.c \
       srcs/parser/error.c \
       srcs/parser/player.c \
       srcs/parser/init.c \
       srcs/parser/utils.c \
       srcs/parser/string_utils.c \
       srcs/parser/string_split.c \
       srcs/parser/string_token_utils.c \
       srcs/parser/map_utils.c \
       srcs/parser/flood_fill.c

OBJ_DIR = objs
OBJS    = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
