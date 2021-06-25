//
// Created by mlays on 24.06.2021.
//
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../minishell/libft/libft.h"

char *get_data_path(char *argument, char **env, char ***arg_data);

int main (int argc, char **argv, char **env)
{
    char *in_name = argv[1];
//    char *cmd = argv[1];
    char *cmd2 = argv[3];
    char *out_name = argv[4];
    int fds_pair[2];

    char **arg_data;
    char *path;

//    path = get_data_path(argv, env, &arg_data);


    int in = open(in_name, O_RDONLY);
    int out = open(out_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);


    execve(path, arg_data, env);

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
