#include "pipex.h"

// ./pipex Makefile rev nl outfile
// ./pipex tolstoy.txt rev nl outfile
// ./pipex Makefile "cat -e" outfile


int main (int argc, char **argv, char **env)
{
    int fds_pair[2];
    int fd_tmp;
    char **arg_data;
    char *path;
	pid_t pid;
    int in;
    int out;

    errno = 0;
    fd_tmp = 0;
    if (argc != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 1);
		exit(1);
	}
	in = open(argv[1], O_RDONLY);
	if (in < 0 || read(in, 0, 0) < 0)
	{
		perror(argv[1]);
		exit(2);
	}
	out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (out < 0 || read(in, 0, 0) < 0)
	{
		perror(argv[4]);
		exit(2);
	}

    int i = 2;
    while (i < 4)
	{
		errno = 0;
    	pipe(fds_pair);
    	pid = fork();
    	if (pid == -1)
		{
    		perror("fork");
    		exit (3);
		}
    	else if (pid == 0)
		{
			if (i == 2)
			{
				dup2(in, 0);
				close(in);
				close(fds_pair[0]);
				dup2(fds_pair[1], 1);
				close(fds_pair[1]);
			}
			else if (i == 3)
			{
				dup2(fd_tmp, 0);
				close(fds_pair[0]);
				close(fds_pair[1]);
				dup2(out, 1);
			}
			path = get_data_path(argv[i], env, &arg_data);
			if (execve(path, arg_data, env) == -1)
			{
				ft_free_line(path);
				ft_free_array(arg_data);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(" : command not found\n", 2);
				exit (4);
			}
			exit(0);
		}
		close (fds_pair[1]);
    	fd_tmp = fds_pair[0];
		i++;
    }
	waitpid(pid, 0, 0);
	close(fds_pair[0]);
	close(fds_pair[1]);
	close(in);
	close(out);
    return (0);
}

//
//int main (int argc, char **argv, char **env)
//{
//	char *in_name = argv[1];
//	char *out_name = argv[4];
//	int fds_pair[2];
//
//	char **arg_data;
//	char *path;
//
//	int in = open(in_name, O_RDONLY);
//	int out = open(out_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
//
//	pipe(fds_pair);
//	pid_t pid = fork();
//	if (pid == 0)
//	{
//		close(fds_pair[0]);
//		dup2(in, 0);
//		close (in);
//		dup2(fds_pair[1], 1);
//		close(fds_pair[1]);
//		path = get_data_path(argv[2], env, &arg_data);
//		execve(path, arg_data, env);
//	}
//	else
//	{
//		pid = fork();
//		if (pid == 0)
//		{
//			close(fds_pair[1]);
//			dup2(fds_pair[0], 0);
//			close(fds_pair[0]);
//			dup2(out, 1);
//			path = get_data_path(argv[3], env, &arg_data);
//			execve(path, arg_data, env);
//		}
//		else
//		{
//			wait(NULL);
//			close(fds_pair[0]);
//			close(fds_pair[1]);
//		}
//	}
//	wait(NULL);
//	return (0);
//}