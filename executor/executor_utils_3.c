/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmikada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:30:03 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 16:30:04 by pmikada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chk_str(char *cmd)
{
	if (ft_strncmpp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmpp(cmd, "$?", 2) == 0)
		return (1);
	return (0);
}

void	ft_chk_child(t_pipe *pipe, t_data *data)
{
	(void)data;
	if (ft_strncmpp(pipe->cmd[0], "echo", 4) == 0)
	{
		if (pipe->cmd[1] == NULL)
			write(1, "\n", 1);
		else
			ft_echo(pipe->cmd);
	}
	else if (ft_strncmpp(pipe->cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (data->path != NULL && ft_strncmpp(pipe->cmd[0], "env", 3) == 0)
		ft_env(data->env);
	exit (0);
}

void	ft_chk_parent(t_pipe *pipe, t_data *data, int *ex_s)
{
	if (ft_strncmpp(pipe->cmd[0], "cd", 2) == 0)
		ft_cd(pipe->cmd[1], &data->env);
	else if (ft_strncmpp(pipe->cmd[0], "export", 6) == 0)
		ft_export(pipe->cmd, data->env, data->export);
	else if (ft_strncmpp(pipe->cmd[0], "unset", 5) == 0)
		ft_unset(pipe->cmd, data->export, data->env);
	else if (ft_strncmpp(pipe->cmd[0], "exit", 4) == 0)
		*ex_s = ft_exit(pipe->cmd);
	else if (ft_strncmpp(pipe->cmd[0], "$?", 2) == 0)
		ft_exit_status(ex_s);
}
