# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 11:04:00 by almirand          #+#    #+#              #
#    Updated: 2022/11/13 13:12:09 by dilopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= VARIABLES =================================

NAME		=	libft.a
INC_DIR		=	../../includes
OBJ_DIR		=	../../obj/libft

BONUS_NAME	=	libft.a

SRC 		=	ft_calloc.c 	\
				ft_isdigit.c	\
				ft_memcpy.c		\
				ft_strlcat.c	\
				ft_strnstr.c	\
				ft_isalnum.c	\
				ft_isprint.c	\
				ft_memmove.c	\
				ft_strlcpy.c	\
				ft_strrchr.c	\
				ft_atoi.c		\
				ft_isalpha.c	\
				ft_memchr.c		\
				ft_memset.c		\
				ft_strlen.c		\
				ft_tolower.c	\
				ft_bzero.c		\
				ft_isascii.c	\
				ft_memcmp.c		\
				ft_strchr.c		\
				ft_strncmp.c	\
				ft_toupper.c	\
				ft_strdup.c		\
				ft_substr.c		\
				ft_strjoin.c	\
				ft_strtrim.c	\
				ft_split.c		\
				ft_strmapi.c	\
				ft_striteri.c	\
				ft_putchar_fd.c	\
				ft_putstr_fd.c	\
				ft_putendl_fd.c	\
				ft_itoa.c		\
				ft_putnbr_fd.c	\

SRC_BONUS	=	ft_lstnew_bonus.c		\
				ft_lstadd_front_bonus.c	\
				ft_lstsize_bonus.c		\
				ft_lstlast_bonus.c		\
				ft_lstadd_back_bonus.c	\
				ft_lstdelone_bonus.c 	\
				ft_lstclear_bonus.c		\
				ft_lstiter_bonus.c		\
				ft_lstmap_bonus.c		\

OBJ			=	$(SRC:.c=.o)
PREFIXED	=	$(addprefix $(OBJ_DIR)/, $(OBJ))

OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

CC			=	gcc

FLAGS		=	-g -Wall -Wextra -Werror -I $(INC_DIR)

YELLOW		=	"\\x1b[33m"
RESET		=	"\\x1b[37m"

# =================================== RULES ===================================

$(NAME):		$(PREFIXED)
	@printf \
	"$(YELLOW)------------------- Libft's files compiled -------------------\n$(RESET)%-33.33s\r"
	@ar -crs $@ $^

$(OBJ_DIR)/%.o:	%.c
	@printf "$(YELLOW)Compiling libft's file -> $(RESET)%-33.33s\r" $<
	@mkdir -p $(OBJ_DIR)/libft
	@$(CC) $(FLAGS) -c $< -o $@

# ================================= FUNCTIONS =================================

all: 	$(NAME)

bonus: 	$(PREFIXED) $(OBJ_BONUS)
	ar -crs $(NAME) $^

clean:
	@rm -f $(OBJ) $(PREFIXED) $(OBJ_BONUS)

fclean:	clean
	@rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re bonus
