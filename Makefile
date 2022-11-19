# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 11:44:09 by dilopez-          #+#    #+#              #
#    Updated: 2022/11/19 08:31:11 by dilopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= VARIABLES =================================

NAME			=	cub3d
LIBFT			=	libft.a
MINILIBX		=	libmlx.a
SRC_DIR			=	src
OBJ_DIR 		=	obj
INC_DIR			=	includes
LIBFT_DIR		=	$(SRC_DIR)/libft
MINILIBX_DIR	=	$(SRC_DIR)/minilibx
GNL_DIR			=	$(SRC_DIR)/get_next_line
LINKS			=	-L . -lmlx -framework OpenGL -framework AppKit

RM				=	rm -rf
CC				=	gcc
CFLAGS			=	-I $(INC_DIR) -g3 -Wall -Werror -Wextra

SRCS			=	$(SRC_DIR)/main.c					\
					$(SRC_DIR)/map.c					\
					$(SRC_DIR)/utils.c					\
					$(SRC_DIR)/color.c					\
					$(SRC_DIR)/parser.c					\
					$(SRC_DIR)/syntax.c					\
					$(GNL_DIR)/get_next_line_utils.c	\
					$(GNL_DIR)/get_next_line.c			\

OBJS			=	$(SRCS:.c=.o)
PREFIXED		=	$(addprefix $(OBJ_DIR)/, $(OBJS))

RED				=	"\\x1b[31m"
GREEN			=	"\\x1b[32m"
YELLOW			=	"\\x1b[33m"
RESET			=	"\\x1b[37m"

# =================================== RULES ===================================

$(NAME):	$(PREFIXED)
	printf \
	"$(YELLOW)------------------ Project's files compiled ------------------\n$(RESET)\n%-33.33s\r"
	printf \
	"$(YELLOW)------------------- Compiling Minilib_x... -------------------$(RESET)%-33.33s\r"
	$(MAKE) -C $(MINILIBX_DIR) 2> logs
	$(RM) logs
	printf \
	"$(YELLOW)----------------- Minilib_x's files compiled ----------------\n$(RESET)\n%-33.33s\r"
	cp $(MINILIBX_DIR)/$(MINILIBX) .
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) .
	$(CC) $(CFLAGS) $(PREFIXED) $(RLFLAGS) $(LIBFT) -o $(NAME)
	echo "\n${GREEN}------------------ Mandatory part compiled! ------------------${RESET}\n"

$(OBJ_DIR)/%.o:	%.c
	mkdir -p $(OBJ_DIR)/$(GNL_DIR)
	printf "$(YELLOW)Compiling project's file >> $(RESET)%-33.33s\r" $<
	$(CC) $(CFLAGS) -c $< -o $@

# ================================= FUNCTIONS =================================

all:	$(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean
	$(RM) $(OBJ) $(OBJ_DIR)
	echo "\n${GREEN}-------------------------- Cleaned! --------------------------${RESET}\n"

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME) $(MINILIBX) $(LIBFT) cub3d.dSYM

re:		fclean all

.PHONY: all clean fclean re bonus
.SILENT: