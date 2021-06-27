#include "pipex.h"

void ft_free_array(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		if (arr[i])
			free(arr[i]);
	free(arr);
}

void ft_free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
}