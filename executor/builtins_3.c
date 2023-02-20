/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmikada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:01:59 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 14:02:01 by pmikada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_insert(char **export, char *s, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmpp(env[i], s, ft_strlen_2(s)) == 0)
		{
			env[i] = ft_strdupp(s);
			return ;
		}
		i++;
	}
	i = 0;
	while (export[i])
	{
		if (ft_strncmpp(export[i], s, ft_strlen_2(s)) == 0)
		{
			if (s[ft_strlen_2(s) + 1] == '=')
				export[i] = ft_strdupp(s);
			return ;
		}
		i++;
	}
	export[i] = ft_strdupp(s);
	export[i + 1] = NULL;
}

static void	ft_del(char **export, char *cmd, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmpp(env[i], cmd, ft_strlenn(cmd)) == 0)
		{
			env[i][0] = '\0';
			return ;
		}
	}
	i = -1;
	while (export[++i])
	{
		if (ft_strncmpp(export[i], cmd, ft_strlenn(cmd)) == 0)
		{
			export[i][0] = '\0';
			return ;
		}
	}
}

void	ft_unset(char **cmd, char **export, char **env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '/')
			printf("unset: %c%s\'%s\n", 96, cmd[i], ERR_EXPORT);
		else if (ft_strlenn(cmd[i]) == ft_strlen_2(cmd[i]))
			ft_del(export, cmd[i], env);
		else
			printf("unset: %c%s\'%s\n", 96, cmd[i], ERR_EXPORT);
		i++;
	}
}

void	ft_exit_status(int *ex_s)
{
	printf("%d%s\n", *ex_s, ERR_CMM);
}

void	ft_in_parent(t_pipe *pipe, int *ex_s, t_data *data, int loop)
{
	if (ft_strncmpp(pipe->cmd[0], "$?", 2))
	{
		if (pipe->path == NULL)
			*ex_s = 127;
		else
			*ex_s = 0;
	}
	if (ft_chk_str(pipe->cmd[0]))
		ft_chk_parent(pipe, data, ex_s);
	ft_close_parent(data, loop);
}
