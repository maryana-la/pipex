#	@rm -f pipex.o
#	@make OBJ="$(OBJ_BON)" all


NAME	=	pipex

CC		=	gcc

CFLAGS 	=	-g -Wall -Wextra -Werror

SRC		:=	pipex.c exec.c pipex_utils.c
SRC_BON	:=	pipex_bonus.c pipex_utils.c exec.c

OBJ 	:=	${SRC:.c=.o}
OBJ_BON	:=	${SRC_BON:.c=.o}

HEADERS	=	libft/libft.h pipex.h

LIBFT	=	libft/libft.a

%.o : %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

bonus: $(LIBFT) $(OBJ_BON)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ_BON) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BON)
	@make clean -C libft/

fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus
