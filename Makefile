# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natali <natali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/26 19:26:13 by natali            #+#    #+#              #
#    Updated: 2021/04/26 21:00:06 by natali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= miniRT

CFLAGS		= -Wall -Wextra -Werror

MLX_FLAGS	= -L./mlx -lmlx -framework OpenGL -framework AppKit -lz

LIBFT_FLAGS = -L./libft -lft

SRCS_DIR	= srcs/

HEADER_DIR	= includes

SRC			= main.c\
			parser/parser.c\
			parser/parse_c.c\
			parser/parse_l.c\
			parser/parse_obj.c\
			rt/raytracing.c\
			rt/light.c\
			rt/sphere.c\
			rt/plane.c\
			rt/square.c\
			rt/triangle.c\
			rt/cylinder.c\
			utils/utils.c\
			utils/parser_utils.c\
			utils/parser_utils2.c\
			utils/vec_utils.c\
			utils/vec_utils2.c\
			utils/window.c\
			utils/hooks.c\
			utils/move_cam.c\
			utils/color.c\
			utils/bmp.c

SRCS 		= $(addprefix $(SRCS_DIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

DEPENDS 	= $(SRCS:.c=.d)

INC			= includes/

LIB_DIR 	= libft/

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ./libft
			@make -C ./mlx
			gcc $(CFLAGS) -I $(INC) $(LIBFT_FLAGS) $(MLX_FLAGS) $^ -o $(NAME)

-include	$(DEPENDS)

%.o:		%.c Makefile
			@gcc $(CFLAGS) -I $(INC) -MMD -MP -c $< -o $@

bonus:		all

norm:
			@norminette $(SRCS_DIR) libft/ includes/minirt.h includes/libft.h

clean:
			@make clean -C ./libft
			@make clean -C ./mlx
			@$(RM) $(OBJS) $(DEPENDS) Superimage.bmp

fclean:		clean
			@make fclean -C ./libft
			@make fclean -C ./mlx
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean