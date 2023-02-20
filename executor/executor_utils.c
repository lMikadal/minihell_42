/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:23:24 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 15:48:32 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_serch_path(t_data *data, t_env *env)
{
	int	i;

	i = 0;
	while (env->tmp_env[i] && ft_strncmpp(PATH, env->tmp_env[i], 5))
		i++;
	if (env->tmp_env[i] != NULL)
		data->path = ft_splitt(&env->tmp_env[i][5], ':');
	else
	{
		data->path = malloc(sizeof(char *));
		data->path = NULL;
	}
	data->env = env->tmp_env;
	data->export = env->export;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*m;
	int		sumlen;
	int		i;
	int		j;

	sumlen = ft_strlenn(s1) + ft_strlenn(s2);
	m = (char *)malloc((sumlen + 1) * sizeof(char));
	if (m == NULL)
		return (0);
	i = 0;
	j = 0;
	while (i < sumlen)
	{
		if (i < ft_strlenn(s1))
			m[i] = s1[i];
		else
			m[i] = s2[j++];
		i++;
	}
	m[i] = '\0';
	free(s1);
	return (m);
}

void	ft_set_ori_fd(t_data *data)
{
	data->ori_fd[0] = dup(STDIN_FILENO);
	data->ori_fd[1] = dup(STDOUT_FILENO);
}

int	ft_count_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;

	tmp = cmd;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_init_pipe(t_data *data)
{
	int	i;

	data->fd_pipe = malloc(sizeof(int *) * (data->count_cmd - 1));
	if (data->fd_pipe == NULL)
		return ;
	i = -1;
	while (++i < data->count_cmd - 1)
	{
		data->fd_pipe[i] = malloc(sizeof(int) * 2);
		if (data->fd_pipe[i] == NULL)
			return ;
	}
	i = -1;
	while (++i < data->count_cmd - 1)
	{
		if (pipe(data->fd_pipe[i]) == -1)
		{
			strerror(errno);
			exit (0);
		}
	}
}
