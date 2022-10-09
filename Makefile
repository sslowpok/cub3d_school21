NAME	=	cub3d
NAME_BONUS	=	cub3d_bonus

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-L$(LIBFT_DIR) -L$(LIBMLX_DIR) -lmlx -Lmlx -framework OpenGL -framework Appkit -lz
RM		=	rm -rf

SRC_DIR	=			src/
SRC_DIR_BONUS	=	src_bonus/
OBJ_DIR	=			obj/
OBJ_DIR_BONUS	=	obj_bonus/
INC_DIR	=			includes/
LIBFT_DIR	=		libft/
LIBMLX_DIR	=		mlx/

SRC_LIST	=	main.c \
				error_handler.c \
				map_parse.c \
				cub3d.c \
				get_next_line.c \
				parse_textures.c \
				raycasting.c \
				draw.c \
				checks.c \
				parse_utils.c \
				hooks.c

SRC_LIST_BONUS	=	main_bonus.c \
				error_handler_bonus.c \
				map_parse_bonus.c \
				cub3d_bonus.c \
				get_next_line_bonus.c \
				parse_textures_bonus.c \
				raycasting_bonus.c \
				draw_bonus.c \
				checks_bonus.c \
				parse_utils_bonus.c \
				hooks_bonus.c

OBJ_LIST	=	$(SRC:%.c=%.o)
OBJ_LIST_BONUS	=	$(SRC_BONUS:%.c=%.o)
HEADERS_LIST	=	cub3d.h
HEADERS_LIST_BONUS	=	cub3d_bonus.h

SRC		=		$(addprefix $(SRC_DIR), $(SRC_LIST))
SRC_BONUS	=	$(addprefix $(SRC_DIR_BONUS), $(SRC_LIST_BONUS))
OBJ		=		$(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))
OBJ_BONUS	=	$(addprefix $(OBJ_DIR_BONUS), $(notdir $(OBJ_LIST_BONUS)))
HEADERS	=	$(addprefix $(INC_DIR), $(HEADERS_LIST))
HEADERS_BONUS	=	$(addprefix $(INC_DIR), $(HEADERS_LIST_BONUS))
LIBFT	=	$(addprefix $(LIBFT_DIR), libft.a)
LIBMLX	=	$(addprefix $(LIBMLX_DIR), libmlx.a)

.PHONY: all clean fclean re

all:	$(LIBFT) $(NAME)

$(LIBFT):
		make bonus -C ./libft/
		make -C ./mlx/

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)%.o:	$(SRC_DIR_BONUS)%.c $(HEADERS_BONUS) | $(OBJ_DIR_BONUS)
				$(CC) $(CFLAGS) -c $< -o $@


$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

#$(OBJ_DIR_BONUS):
#		mkdir $(OBJ_DIR_BONUS)
	
clean:	
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_DIR_BONUS)
	@make clean -C ./libft/
	@make clean -C ./mlx/

fclean:	clean
		@$(RM) $(NAME) $(LIBFT)
		@$(RM) $(NAME_BONUS)
	
re:		fclean $(OBJ_DIR) all

bonus: $(LIBFT)
	make NAME="$(NAME_BONUS)" OBJ="$(OBJ_BONUS)" OBJ_DIR="$(OBJ_DIR_BONUS)" HEADERS="$(HEADERS_BONUS)" SRC_DIR="$(SRC_DIR_BONUS)" all

$(OBJ_DIR_BONUS)%.o:	$(SRC_DIR_BONUS)%.c $(HEADERS_BONUS) | $(OBJ_DIR_BONUS)
				$(CC) $(CFLAGS) -c $< -o $@