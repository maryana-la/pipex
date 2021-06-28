#include "pipex.h"

char *get_data_path(char *argument, char **env, char ***arg_data)
{
    char **path;
    char *path_tmp;
    char *tmp;
    char *get_pwd;
    char *exec;
    int i;

    if (ft_strncmp(argument, "./", 2) == 0)
	{
    	exec = ft_substr(argument, 2, ft_strlen(argument) - 2);
    	*arg_data = ft_split(exec, ' ');
    	ft_free_line(exec);
    	i = -1;
		while (env[++i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				break;
		}
		get_pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
		tmp = get_pwd;
		get_pwd = ft_strjoin(get_pwd, "/");
		ft_free_line(tmp);
		tmp = get_pwd;
		get_pwd = ft_strjoin(get_pwd, *arg_data[0]);
		ft_free_line(tmp);
		if (access(get_pwd, X_OK) != 0)
		{
			ft_free_line(get_pwd);
			perror (argument);
			exit (1);
		}
		return (get_pwd);
	}

    *arg_data = ft_split(argument, ' ');
    if (!(*arg_data))
    	exit(-1);
    i = -1;
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
		if (access(path_tmp, F_OK | X_OK) == 0)
		{
			ft_free_array(path);
			return (path_tmp);
		}
        free(path_tmp);
    }
    return (0);
}

