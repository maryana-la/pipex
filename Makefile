



#all:
#	gcc -g pipex.c exec.c pipex_utils.c libft/libft.a -opipex
#
#bonus:
#	gcc -g pipex_bonus.c pipex_bonus_2.c pipex_bonus_utils.c exec.c libft/libft.a -obonus
#
#clean:
#	rm -rf all
#	rm -rf bonus
#
#re: clean all
## make OBJ="$(OBJ_BON)" all
#


NAME	=	pipex

CC		=	gcc

CFLAGS 	=	-g

SRC		:=	pipex.c exec.c pipex_utils.c
SRC_BON	:=	pipex_bonus.c pipex_utils.c exec.c

OBJ 	:=	${SRC:.c=.o}
OBJ_BON	:=	${SRC_BON:.c=.o}

HEADERS	=	libft/libft.h libft/get-next-line/get_next_line.h pipex.h

LIBFT	=	libft/libft.a

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

bonus: $(OBJ_BON) $(LIBFT)
	rm -f pipex.o
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ_BON) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BON)
	make clean -C libft/

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus
