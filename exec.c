//
// Created by mlays on 25.06.2021.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../minishell/libft/libft.h"

char *get_data_path(char *argument, char **env, char ***arg_data)
{

    char **path;
    char *path_tmp;
    char *tmp;
    int fd;
    *arg_data = ft_split(argument, ' ');

    int i = -1;
    while (env[++i])
    {
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
        path_tmp = ft_strjoin(path_tmp, *arg_data[0]);
        fd = open(path_tmp, O_RDONLY);
        if (fd > 0)
            return(path_tmp);
        close(fd);
        free(path_tmp);
        path_tmp = "\0";
    }
}

