#include "executor.h"

void	ft_close(t_data *data, int loop)
{
	while (loop < data->count_cmd - 1)
	{
		close(data->fd_pipe[loop][0]);
		close(data->fd_pipe[loop][1]);
		loop++;
	}
}

void	ft_close_parent(t_data *data, int loop)
{
	if (data->count_cmd != 1)
	{
		if (loop == 0)
			close(data->fd_pipe[loop][1]);
		else if (loop == data->count_cmd - 1)
			close(data->fd_pipe[loop - 1][0]);
		else
		{
			close(data->fd_pipe[loop - 1][0]);
			close(data->fd_pipe[loop][1]);
		}
	}
}

void	ft_here_doc(t_pipe *p, t_cmd *cmd, int idx, int tmp)
{
	char	name[30];
	char	*str;
	int		fd;

	ft_strlcpyy(name, "/tmp/tmp", 8);
	str = ft_itoaa(tmp);
	ft_strlcatt(name, str, 100);
	free(str);
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (ft_strcmpp(str, cmd->i_tab[idx], ft_strlenn(str)))
			break ;
		write(fd, str, ft_strlenn(str));
		free(str);
	}
	free(str);
	close(fd);
	p->infile = open(name, O_RDWR);
}