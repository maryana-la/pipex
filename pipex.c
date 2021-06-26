#include "pipex.h"

//./a.out Makefile rev nl out



int main (int argc, char **argv, char **env)
{
    char *in_name = argv[1];
    char *out_name = argv[4];
    int fds_pair[2];

    char **arg_data;
    char *path;

    int in = open(in_name, O_RDONLY);
    int out = open(out_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    pipe(fds_pair);
    pid_t pid = fork();
    if (pid == 0)
    {
        close(fds_pair[0]);
        dup2(in, 0);
        close (in);
        dup2(fds_pair[1], 1);
        close(fds_pair[1]);
        path = get_data_path(argv[2], env, &arg_data);
        execve(path, arg_data, env);
    }
    else
    {
        pid = fork();
        if (pid == 0)
        {
            close(fds_pair[1]);
            dup2(fds_pair[0], 0);
            close(fds_pair[0]);
            dup2(out, 1);
            path = get_data_path(argv[3], env, &arg_data);
            execve(path, arg_data, env);
        }
        else
        {
            close(fds_pair[0]);
            close(fds_pair[1]);
        }

    }
    waitpid(pid, 0, 0);
    return (0);
}
