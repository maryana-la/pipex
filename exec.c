#include "pipex.h"

char *get_data_path(char *argument, char **env, char ***arg_data)
{
    char **path;
    char *path_tmp;
    char *tmp;
    int fd;

    *arg_data = ft_split(argument, ' ');
    if (!*arg_data)
    	exit(-1);

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
	ft_free_line(tmp);

    if (!path)
	{
		ft_free_array(*arg_data);
		ft_free_line(tmp);
		exit(-1);
	}
    i = -1;
    path_tmp = NULL;
    while (path[++i])
    {
        path_tmp = ft_strjoin(path[i], "/");
        tmp = path_tmp;
        path_tmp = ft_strjoin(path_tmp, *arg_data[0]);
		ft_free_line(tmp);
		if (access(path_tmp, F_OK) == 0)
		{
			ft_free_array(path);
			return (path_tmp);
		}
        free(path_tmp);
    }
    return (0);
}

