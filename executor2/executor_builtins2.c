#include "executor.h"

static int	ft_strcmp_ori(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}

static void	ft_sort(char **tmp, int c_env)
{
	int		i;
	int		j;
	char	*tmp_t;

	i = 0;
	while (i < c_env - 1)
	{
		j = 0;
		while (j < c_env - i - 1)
		{
			if (ft_strcmp_ori(tmp[j], tmp[j + 1]) > 0)
			{
				tmp_t = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = tmp_t;
			}
			j++;
		}
		i++;
	}
}

static void	ft_write(char **tmp, int c_env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < c_env)
	{
		if (tmp[i][0] != '\0')
		{
			write(1, "declare - x ", 12);
			j = -1;
			while (++j < ft_strlen_2(tmp[i]))
				write(1, &tmp[i][j], 1);
			if (tmp[i][j] == '=')
				printf("=\"%s\"\n", &tmp[i][++j]);
			else
				write(1, "\n", 1);
		}
	}
}

void	ft_print_export(char **env)
{
	char	**tmp;
	int		c_env;
	int		i;

	c_env = ft_strlen_c2d(env);
	tmp = malloc(sizeof(char *) * c_env);
	if (tmp == NULL)
		return ;
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdupp(env[i]);
	tmp[i] = NULL;
	ft_sort(tmp, c_env);
	ft_write(tmp, c_env);
	ft_free_c2d(tmp);
}

int	ft_add_export(t_pipe *p, t_data *data, int mode)
{
	int		c_add;
	char	**n_env;
	int		i;
	int		j;
	int		r;

	c_add = ft_count_add(p->cmd, data->env);
	n_env = malloc(sizeof(char *) * (ft_strlen_c2d(data->env) + c_add + 1));
	i = -1;
	while (data->env[++i])
		n_env[i] = ft_strdupp(data->env[i]);
	j = 1;
	r = 0;
	while (p->cmd[j])
	{
		if (((p->cmd[j][0] >= 'A' && p->cmd[j][0] <= 'Z') \
			|| (p->cmd[j][0] >= 'a' && p->cmd[j][0] <= 'z') \
			|| p->cmd[j][0] == '_'))
			ft_insert_export(&i, j, p, n_env);
		else if (mode == 1)
		{
			printf("export: %c%s\'%s\n", 96, p->cmd[j], ERR_EXPORT);
			r = 1;
		}
		j++;
	}
	n_env[i] = NULL;
	ft_free_c2d(data->env);
	data->env = NULL;
	data->env = n_env;
	return (r);
}