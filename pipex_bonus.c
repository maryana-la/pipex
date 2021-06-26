#include "pipex.h"

int pipex_bonus_2(int argc, char **argv, char **env);

int main(int argc, char *argv[], char **env)
{
	char *in_name;
	char *out_name;
	char **arg_data;
	char *path;
	int fd_in;
	int fd_out;
	int fd[2];
	pid_t pid;
	int fdd;
	int i;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex_bonus_2(argc, argv, env);
	else {
		in_name = argv[1];
		out_name = argv[argc - 1];
		fd_in = open(in_name, O_RDONLY);
		fd_out = open(out_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

		fdd = 0;
		i = 1;
		while (i < (argc - 2)) {
			pipe(fd);
			if ((pid = fork()) == -1) {
				perror("fork");
				exit(1);
			} else if (pid == 0) {
				if (i == 1)
					dup2(fd_in, 0);
				else
					dup2(fdd, 0);
				if (i + 3 != argc)
					dup2(fd[1], 1);
				else if (i + 3 == argc)
					dup2(fd_out, 1);
				close(fd[0]);
				path = get_data_path(argv[i + 1], env, &arg_data);
				execve(path, arg_data, env);
				exit(1);
			} else {
				wait(NULL);
				close(fd[1]);
				fdd = fd[0];
				i++;
			}
		}
	}
	return(0);
}