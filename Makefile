# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgyles <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 10:19:01 by rgyles            #+#    #+#              #
#    Updated: 2019/01/30 13:56:59 by rgyles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = fractol

LIB = libfdf.a

MLX = minilibx_macos/libmlx.a

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

OBJ = $(SRC:.c=.o) 

LIB_SRC = $(addprefix libft/, $(shell ls libft | grep .c))

LIB_OBJ = $(LIB_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(EXE)

$(EXE): $(OBJ) $(LIB) $(MLX)
	gcc $(FLAGS) -o $(EXE) $(OBJ) $(LIB) -L minilibx_macos -l mlx -framework OpenGL -framework Appkit -framework OpenCL

.c.o:
	gcc $(FLAGS) -Ilibft -o $@ -c $<

$(LIB): $(LIB_OBJ)
	@ar rc $(LIB) $(LIB_OBJ)
	@ranlib $(LIB)

$(MLX):
	cd minilibx_macos && make

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(LIB_OBJ)

fclean: clean
	/bin/rm -f $(EXE)
	/bin/rm -f $(LIB)
	cd minilibx_macos && make clean

re: fclean all

m: all
	./fractol mandelbrot

j: all
	./fractol julia
	
t: all
	./fractol tricorn

b: all
	./fractol burning_ship

.PHONY: all clean fclean re
