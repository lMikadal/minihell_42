#include "executor.h"

void	ft_free_c2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_free_i2d(int **s, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(s[i]);
	free(s);
}

void	ft_free_data(t_data *data)
{
	if (data->path != NULL)
		ft_free_c2d(data->path);
	free(data->child_pid);
	if (data->count_cmd > 1)
		ft_free_i2d(data->fd_pipe, data->count_cmd - 1);
}

void	ft_free_pipe(t_pipe *pipe)
{
	if (pipe->path != NULL)
		free(pipe->path);
}