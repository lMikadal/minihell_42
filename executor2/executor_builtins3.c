#include "executor.h"

int	ft_count_add(char **cmd, char **env)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (cmd[i])
	{
		if (((cmd[i][0] >= 'A' && cmd[i][0] <= 'Z') \
			|| (cmd[i][0] >= 'a' && cmd[i][0] <= 'z') \
			|| cmd[i][0] == '_') \
			&& ft_chk_dup(cmd[i], env) && ft_chk_dup(cmd[i], &cmd[i + 1]))
			count++;
		i++;
	}
	return (count);
}

int	ft_chk_dup(char *s, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmpp(s, env[i], ft_strlenn(s)) == 0)
			return (0);
	}
	return (1);
}

int	ft_chk_dup2(char *s, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmpp(s, env[i], ft_strlenn(env[i])) == 0)
			return (0);
	}
	return (1);
}

void	ft_insert_export(int *i, int j, t_pipe *p, char **n_env)
{
	int	k;

	k = -1;
	while (n_env[++k])
	{
		if (ft_strncmpp(p->cmd[j], n_env[k], ft_strlen_2(p->cmd[j])) == 0)
		{
			free(n_env[k]);
			n_env[k] = NULL;
			n_env[k] = ft_strdupp(p->cmd[j]);
			return ;
		}
	}
	n_env[*i] = ft_strdupp(p->cmd[j]);
	*i += 1;
}

int		ft_unset(t_pipe *p, t_data *data, int mode)
{
	int		c_env;
	int		i;
	char	**n_env;
	int		j;
	int		r;

	c_env = ft_strlen_c2d(data->env);
	i = 1;
	r = 0;
	while(p->cmd[i])
	{
		if (ft_chk_dup(p->cmd[i], data->env) == 0)
			c_env--;
		else if (mode == 1 && ((p->cmd[i][0] <= 'A' || p->cmd[i][0] >= 'Z') \
			&& (p->cmd[i][0] <= 'a' || p->cmd[i][0] >= 'z') \
			&& p->cmd[i][0] != '_'))
		{
			printf("unset: %c%s\'%s\n", 96, p->cmd[i], ERR_EXPORT);
			r = 1;
		}
		i++;
	}
	n_env = malloc(sizeof(char *) * (c_env + 1));
	i = -1;
	j = 0;
	while (data->env[++i])
	{
		if (ft_chk_dup2(data->env[i], p->cmd))
			n_env[j++] = ft_strdupp(data->env[i]);
	}
	n_env[j] = NULL;
	ft_free_c2d(data->env);
	data->env = NULL;
	data->env = n_env;
	return (r);
}
