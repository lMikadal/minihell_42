/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:32:49 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 16:16:49 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_chk_path(t_pipe *pipe, t_data *data)
{
	int		i;
	char	*chk;

	i = -1;
	while (data->path != NULL && data->path[++i])
	{
		chk = ft_strjoinn("", pipe->cmd[0]);
		if (access(chk, F_OK | X_OK) == 0)
			return (chk);
		free(chk);
		chk = ft_strjoinn(data->path[i], pipe->cmd[0]);
		if (access(chk, F_OK | X_OK) == 0)
			return (chk);
		free(chk);
	}
	return (NULL);
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

static void	ft_close(t_data *data, int loop)
{
	while (loop < data->count_cmd - 1)
	{
		close(data->fd_pipe[loop][0]);
		close(data->fd_pipe[loop][1]);
		loop++;
	}
}

static void	ft_fork(t_cmd *cmd, t_data *data, int loop, int *ex_s)
{
	t_pipe	pipe;

	pipe.cmd = cmd->cmd;
	pipe.path = ft_chk_path(&pipe, data);
	data->child_pid[loop] = fork();
	if (data->child_pid[loop] == 0)
	{
		ft_set_pipe(&pipe, data, cmd, loop);
		ft_close(data, loop);
		if (ft_chk_str(pipe.cmd[0]))
			ft_chk_child(&pipe, data);
		else
			execve(pipe.path, pipe.cmd, data->env);
		if (pipe.cmd[0][0] != '\0')
			printf("%s%s\n", pipe.cmd[0], ERR_CMM);
		exit (1);
	}
	else if (data->child_pid[loop] > 0)
		ft_in_parent(&pipe, ex_s, data, loop);
	free(pipe.path);
}

void	ft_executor(t_cmd *cmd, t_env *env, int *ex_s)
{
	t_data	data;
	int		i;

	ft_serch_path(&data, env);
	i = -1;
	while (data.path != NULL && data.path[++i])
		data.path[i] = ft_strjoin_free(data.path[i], "/");
	ft_set_ori_fd(&data);
	data.count_cmd = ft_count_cmd(cmd);
	data.child_pid = malloc(sizeof(int) * data.count_cmd);
	if (data.child_pid == NULL)
		return ;
	if (data.count_cmd > 1)
		ft_init_pipe(&data);
	i = -1;
	while (cmd)
	{
		ft_fork(cmd, &data, ++i, ex_s);
		cmd = cmd->next;
	}
	i = -1;
	while (++i < data.count_cmd)
		waitpid(data.child_pid[i], NULL, 0);
	ft_free_st(&data);
}
