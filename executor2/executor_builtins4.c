#include "executor.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

static void	ft_print_exit(char **cmd)
{
	int	j;

	j = -1;
	while (cmd[1][++j])
	{
		if (ft_isdigit(cmd[1][j]) == 0)
		{
			printf("exit: %s%s\n", cmd[1], ERR_EXIT_N);
			exit (255);
		}
	}
}

void	ft_exit(t_pipe *p, t_data *data)
{
	int	i;
	int	ex;

	printf("exit\n");
	i = 0;
	while (p->cmd[i])
		i++;
	if (i == 1)
	{
		ft_free_pipe(p);
		ft_free_data(data);
		exit(0);
	}
	else if (i >= 2)
	{
		ft_print_exit(p->cmd);
		if (i == 2)
		{
			ex = ft_atoi(p->cmd[1]);
			ft_free_pipe(p);
			ft_free_data(data);
			exit (ex);
		}
		else
		{
			printf("exit: %s\n", ERR_EXIT);
			*(data->ex_s) = 1;
			return ;
		}
	}
	*(data->ex_s) = 0;
}
