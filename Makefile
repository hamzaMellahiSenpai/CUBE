# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 23:25:02 by hmellahi          #+#    #+#              #
#    Updated: 2021/01/08 16:58:30 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
ARG = -c
SRC = 	cub3D.c                         graphics/hud.c                  graphics/vector.c               includes/func_utils3.c   \
	  	maths.c                         parsing_file/map_validation.c   play_music.c \
		effects.c                       graphics/mini_map.c             includes/ft_split.c             includes/get_next_line.c    \
		objects/player.c                parsing_file/read_file.c        save.c        errors.c                                  \
		graphics/ray.c                  includes/func_utils.c           includes/lst.c                  objects/sprite.c       \
		parsing_file/reading_infos.c    ui.c  events_handler.c                graphics/rendering.c      objects/helpers.c \
		includes/func_utils2.c          includes/sf_malloc.c            parsing_file/loading_assets.c   parsing_file/validiting_infos.c 
CC  = @gcc
MLX = -lmlx -framework OpenGL -framework AppKit -g
NAME = cub3D
OUT = $(SRC:.c=.o)

all : ${NAME}
	
${NAME}:
	gcc ${SRC} $(FLAGS) $(MLX) -D BONUS=0 -o ${NAME}
clean:
	rm -rf ${OUT}

fclean: clean
		rm -rf ${NAME}

re: fclean all

bonus:
	gcc $(FLAGS) $(SRC) -D BONUS=1 $(MLX) -o ${NAME}
