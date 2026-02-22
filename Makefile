# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 11:53:52 by rakman            #+#    #+#              #
#    Updated: 2026/02/22 23:50:33 by rakman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./lib/minilibx-linux -I./lib/get_next_line

MLX_DIR = lib/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42paris/minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

SRC_MAIN = src/main.c

SRC_CORE = src/01_core/00_game_loop.c \
           src/01_core/01_utils.c

SRC_EVENTS = src/04_events/00_key_handler.c \
             src/04_events/01_move_player.c \
             src/04_events/02_rotate_player.c

SRC_EXIT = src/05_exit/00_clean_exit.c \
           src/05_exit/01_error.c

VALIDATE_DIR = src/00_initialize_game/00_validate_file/
VALIDATE = 00_validate_coordinator.c \
           01_populate_rawdata.c \
           02_validate_config_arrays.c \
           03_validate_texture_lines.c \
           04_validate_color_lines.c \
           05_validate_map_grid.c \
           06_is_enclosed_by_walls.c \
           07_has_double_map.c \
           98_validate_utils.c \
           99_validate_utils.c

SRC_INITIALIZE_GAME = $(addprefix $(VALIDATE_DIR), $(VALIDATE)) \
                       src/00_initialize_game/01_parse_file/00_parse_coordinator.c \
                       src/00_initialize_game/01_parse_file/01_parse_textures.c \
                       src/00_initialize_game/01_parse_file/02_parse_colors.c \
                       src/00_initialize_game/01_parse_file/03_normalize_map_grid.c \
                       src/00_initialize_game/01_parse_file/04_parse_map_grid.c \
                       src/00_initialize_game/01_parse_file/98_parse_utils.c \
                       src/00_initialize_game/02_init_game/00_init_coordinator.c \
                       src/00_initialize_game/02_init_game/01_init_textures.c \
                       src/00_initialize_game/02_init_game/02_init_camera_vectors.c

SRC_RAYCASTING = src/02_raycasting/00_dda.c \
                 src/02_raycasting/01_math_utils.c \
                 src/02_raycasting/02_raycaster.c

SRC_RENDER = src/03_render/00_render_frame.c \
             src/03_render/01_draw_walls.c

SRC_LIBFT = lib/libft/ft_atoi.c \
            lib/libft/ft_bzero.c \
            lib/libft/ft_calloc.c \
            lib/libft/ft_isalnum.c \
            lib/libft/ft_isalpha.c \
            lib/libft/ft_isascii.c \
            lib/libft/ft_isdigit.c \
            lib/libft/ft_isprint.c \
            lib/libft/ft_itoa.c \
            lib/libft/ft_lstadd_back.c \
            lib/libft/ft_lstadd_front.c \
            lib/libft/ft_lstclear.c \
            lib/libft/ft_lstdelone.c \
            lib/libft/ft_lstiter.c \
            lib/libft/ft_lstlast.c \
            lib/libft/ft_lstmap.c \
            lib/libft/ft_lstnew.c \
            lib/libft/ft_lstsize.c \
            lib/libft/ft_memchr.c \
            lib/libft/ft_memcmp.c \
            lib/libft/ft_memcpy.c \
            lib/libft/ft_memmove.c \
            lib/libft/ft_memset.c \
            lib/libft/ft_putchar_fd.c \
            lib/libft/ft_putendl_fd.c \
            lib/libft/ft_putnbr_fd.c \
            lib/libft/ft_putstr_fd.c \
            lib/libft/ft_split.c \
            lib/libft/ft_strchr.c \
            lib/libft/ft_strdup.c \
            lib/libft/ft_striteri.c \
            lib/libft/ft_strjoin.c \
            lib/libft/ft_strlcat.c \
            lib/libft/ft_strlcpy.c \
            lib/libft/ft_strlen.c \
            lib/libft/ft_strmapi.c \
            lib/libft/ft_strncmp.c \
            lib/libft/ft_strnstr.c \
            lib/libft/ft_strrchr.c \
            lib/libft/ft_strtrim.c \
            lib/libft/ft_substr.c \
            lib/libft/ft_tolower.c \
            lib/libft/ft_toupper.c

SRC_GNL = lib/get_next_line/get_next_line.c \
          lib/get_next_line/get_next_line_utils.c

SRCS = $(SRC_MAIN) $(SRC_CORE) $(SRC_EVENTS) $(SRC_EXIT) \
       $(SRC_INITIALIZE_GAME) $(SRC_RAYCASTING) $(SRC_RENDER) $(SRC_LIBFT) $(SRC_GNL)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(MLX_DIR)/Makefile:
	/usr/bin/git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)/Makefile
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -f "$(MLX_DIR)/Makefile" ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
