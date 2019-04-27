# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgyles <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 10:19:01 by rgyles            #+#    #+#              #
#    Updated: 2019/04/27 18:57:22 by rgyles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

LIB_DIR = libft

LIB = $(LIB_DIR)/libft.a

MLX_DIR = minilibx_macos

MLX = $(MLX_DIR)/libmlx.a

SRC_DIR = sources

SRC = main.c \
		ft_image_man.c \
		ft_key_press.c \
		ft_mouse_press.c \
		ft_mandelbrot.c \
		ft_julia.c \
		ft_burning_ship.c \
		ft_tricorn.c \
		ft_gpu.c \
		ft_gpu_init.c\
		ft_get_source_file.c

OBJ_DIR = objects

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	gcc $(FLAGS) -o $(NAME) -I includes -I libft $(OBJ) $(LIB) $(MLX) -framework OpenGL -framework Appkit -framework OpenCL

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/fractol.h | $(OBJ_DIR)
	gcc $(FLAGS) -I includes -o $@ -c $<

$(LIB):
	@make -C $(LIB_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@make -C $(MLX_DIR) clean

re: fclean all

m: all
	./fractol mandelbrot

j: all
	./fractol julia
	
t: all
	./fractol tricorn

b: all
	./fractol burning_ship

.PHONY: all clean fclean re m j t b
