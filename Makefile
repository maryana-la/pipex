all:
	gcc -g pipex.c exec.c libft/libft.a -opipex

bonus:
	gcc -g pipex_bonus.c pipex_bonus_2.c exec.c libft/libft.a -obonus

clean:
	rm -rf all
	rm -rf bonus

re: clean all

.PHONY: all clean bonus