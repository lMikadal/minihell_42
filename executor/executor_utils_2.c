/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 23:19:57 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/11 00:00:01 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoinn(char *s1, char *s2)
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
	return (m);
}

static void	ft_here_doc(t_pipe *pipe, t_cmd *cmd, int index, int tmp)
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
		if (ft_strcmpp(str, cmd->i_tab[index], ft_strlenn(str)))
			break ;
		write(fd, str, ft_strlenn(str));
		free(str);
	}
	free(str);
	close(fd);
	pipe->infile = open(name, O_RDWR);
}

static int	ft_chk_infile(t_pipe *pipe, t_cmd *cmd)
{
	int			i;
	static int	tmp;

	i = -1;
	tmp = 0;
	while (cmd->i_tab[++i])
	{
		if (cmd->sign_i[i] == 1)
			pipe->infile = open(cmd->i_tab[i], O_RDWR);
		else if (cmd->sign_i[i] == 2)
			ft_here_doc(pipe, cmd, i, tmp++);
		if (cmd->i_tab[i + 1] != NULL)
			close(pipe->infile);
	}
	if (cmd->i_tab[0] != NULL)
		return (1);
	return (0);
}

static int	ft_chk_outfile(t_pipe *pipe, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->o_tab[++i])
	{
		if (cmd->sign_o[i] == 1)
		{
			pipe->outfile = open(cmd->o_tab[i], \
				O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		else if (cmd->sign_o[i] == 2)
		{
			pipe->outfile = open(cmd->o_tab[i], \
				O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		if (cmd->o_tab[i + 1] != NULL)
			close(pipe->outfile);
	}
	if (cmd->o_tab[0] != NULL)
		return (1);
	return (0);
}

void	ft_set_pipe(t_pipe *pipe, t_data *data, t_cmd *cmd, int loop)
{
	if (loop == 0 && cmd->i_tab[0] == NULL)
		dup2(data->ori_fd[0], 0);
	else if (ft_chk_infile(pipe, cmd))
		dup2(pipe->infile, 0);
	else
		dup2(data->fd_pipe[loop - 1][0], 0);
	if (loop == data->count_cmd - 1 && cmd->o_tab[0] == NULL)
		dup2(data->ori_fd[1], 1);
	else if (ft_chk_outfile(pipe, cmd))
		dup2(pipe->outfile, 1);
	else
		dup2(data->fd_pipe[loop][1], 1);
}
