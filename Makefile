all:
	gcc -g pipex.c exec.c ../libft/libft.a

bonus:
	gcc -g pipex_bonus.c exec.c ../libft/libft.a
