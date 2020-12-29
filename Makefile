# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 23:25:02 by hmellahi          #+#    #+#              #
#    Updated: 2020/10/31 01:32:54 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
ARG = -c
SRC = *.c */*.c
CC  = @gcc
MLX = -lmlx -framework OpenGL -framework AppKit -g
NAME = Cub3d

all : ${NAME}
	
${NAME}:
	gcc -g *.c  */*.c $(FLAGS) $(MLX) -D BONUS=0 -o ${NAME}
clean:
	rm -rf *.o

fclean: clean
		rm -rf ${NAME}

re: fclean all

bonus:
	gcc $(FLAGS) $(SRC) -D BONUS=1 $(MLX) -o ${NAME}