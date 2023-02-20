/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 22:09:33 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 16:16:44 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_st(t_data *data)
{
	free(data->child_pid);
	if (data->count_cmd > 1)
		ft_free_int_2d(data->fd_pipe, data->count_cmd - 1);
}

void	ft_free_ch_2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_free_int_2d(int **s, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(s[i]);
	free(s);
}

void	ft_free_export(char **new, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(new[i]);
	free(new);
}
