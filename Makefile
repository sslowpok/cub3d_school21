NAME	=	cub3d

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-L$(LIBFT_DIR) -L$(LIBMLX_DIR) -lmlx -Lmlx -framework OpenGL -framework Appkit -lz
RM		=	rm -rf

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INC_DIR	=	includes/
LIBFT_DIR	=	libft/
LIBMLX_DIR	=	mlx/

SRC_LIST	=	main.c \
				error_handler.c \
				map_parse.c \
				cub3d.c \
				get_next_line.c \
				parse_textures.c


OBJ_LIST	=	$(SRC:%.c=%.o)
HEADERS_LIST	=	cub3d.h

SRC		=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ		=	$(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))
HEADERS	=	$(addprefix $(INC_DIR), $(HEADERS_LIST))
LIBFT	=	$(addprefix $(LIBFT_DIR), libft.a)
LIBMLX	=	$(addprefix $(LIBMLX_DIR), libmlx.a)

.PHONY: all clean fclean re

all:	$(LIBFT) $(NAME)

$(LIBFT):
		make bonus -C ./libft/
		make -C ./mlx/

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR):
		mkdir $(OBJ_DIR)
	
clean:	
	$(RM) $(OBJ_DIR)
	make clean -C ./libft/
	make clean -C ./mlx/

fclean:	clean
		$(RM) $(NAME) $(LIBFT)
	
re:		fclean $(OBJ_DIR) all