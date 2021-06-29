#include "pipex.h"

char	*get_pwd_exec(char *argument, char **env, t_pipex *pip)
{
	char	*tmp;
	char	*get_path;
	char	*exec;
	int		i;

	exec = ft_substr(argument, 2, ft_strlen(argument) - 2);
	pip->arg_data = ft_split(exec, ' ');
	ft_free_line(exec);
	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			break ;
	get_path = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
	tmp = get_path;
	get_path = ft_strjoin(get_path, "/");
	ft_free_line(tmp);
	exec = ft_strjoin(get_path, pip->arg_data[0]);
	ft_free_line(get_path);
	if (access(exec, X_OK) != 0)
	{
		ft_free_line(exec);
		ft_error_exit(argument, FILE_ERR);
	}
	return (exec);
}

char	*get_path_from_env(char **env)
{
	int		i;
	char	*path;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			return (path);
		}
	}
	return (0);
}

char	*find_exec_file (t_pipex *pip, char **path_arr)
{
	int		i;
	char	*exec_path;
	char	*tmp;

	i = -1;
	exec_path = NULL;
	while (path_arr[++i])
	{
		exec_path = ft_strjoin(path_arr[i], "/");
		tmp = exec_path;
		exec_path = ft_strjoin(exec_path, pip->arg_data[0]);
		ft_free_line(tmp);
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			ft_free_array(path_arr);
			return (exec_path);
		}
		ft_free_line(exec_path);
	}
	ft_free_array(path_arr);
	return (0);
}

char	*get_data_path(char *argument, char **env, t_pipex *pip)
{
	char	**path_arr;
	char	*path_str;

	if (ft_strncmp(argument, "./", 2) == 0)
		return (get_pwd_exec(argument, env, pip));
	pip->arg_data = ft_split(argument, ' ');
	if (!(pip->arg_data))
		ft_error_exit("malloc", MALLOC_ERR);
	path_str = get_path_from_env(env);
	path_arr = ft_split(path_str, ':');
	if (!path_arr)
	{
		ft_free_array(pip->arg_data);
		ft_free_line(path_str);
		exit(MALLOC_ERR);
	}
	ft_free_line(path_str);
	return (find_exec_file(pip, path_arr));
}
