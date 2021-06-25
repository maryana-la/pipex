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

int main (int argc, char **argv, char **env)
{
    char *in_name = argv[1];
    char *cmd = argv[1];
    char *cmd2 = argv[3];
    char *out_name = argv[4];
    int fds_pair[2];
    int fd;

    char **arg_data;
    char **path;
    char *path_tmp;
    char *path_final;
    char *tmp;

//    int in = open(in_name, O_RDONLY);
//    int out = open(out_name, O_CREAT | O_RDWR, S_IRWXG | S_IRWXO);

    arg_data = ft_split(argv[1], ' ');

    int i = -1;
    while (env[++i])
    {
//        printf("%s\n", env[i]);
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            tmp = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
            break;
        }
    }
    path = ft_split(tmp, ':');
    i = -1;
    path_tmp = NULL;
    while (path[++i])
    {
        path_tmp = ft_strjoin(path[i], "/");
        path_tmp = ft_strjoin(path_tmp, cmd);
        fd = open(path_tmp, O_RDONLY);
        if (fd > 0)
            break;
        close (fd);
        free(path_tmp);
        path_tmp = "\0";
    }

    execve(path_tmp, arg_data, env);

//    pipe(fds_pair);
//
//    pid_t pid = fork();
//    if (pid == 0)
//    {
//        dup2(in, 0);
//        close (in);
//        close(fds_pair[0]);
//        dup2(fds_pair[1], 1);
//        close(fds_pair[1]);
////        dup2(in, 0);
////        close(in);
////        dup2(fds_pair[1], 1);
////        close(fds_pair[1]);
//        execlp(cmd, cmd, NULL);
//    }
//    else
//    {
//        dup2(fds_pair[1], out);
//        close(fds_pair[1]);
//        dup2(fds_pair[0],0);
//        close(fds_pair[0]);
////        int total_count = 0;
////        size_t count;
////        char buffer[4096];
////        while((count = read(fds_pair[0], buffer, sizeof(buffer))) > 0)
////            total_count += count;
//        execlp(cmd2, cmd2, NULL);
//        waitpid(pid, 0, 0);
////        printf("%d\n", total_count);
//    }
    return (0);
}
