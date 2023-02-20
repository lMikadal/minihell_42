/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmikada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:44:40 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 01:44:41 by pmikada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_write_export(char **new, int loop)
{
	int	i;
	int	j;

	i = -1;
	while (++i < loop)
	{
		if (new[i][0] != '\0')
		{
			write(1, "declare - x ", 12);
			j = -1;
			while (++j < ft_strlen_2(new[i]))
				write(1, &new[i][j], 1);
			if (new[i][j] == '=')
				printf("=\"%s\"\n", &new[i][++j]);
			else
				write(1, "\n", 1);
		}
	}
}

static void	ft_export_cmp(char **new, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp_ori(new[j], new[j + 1]) > 0)
			{
				tmp = new[j];
				new[j] = new[j + 1];
				new[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_sort_export(char **env, char **export)
{
	int		i;
	int		count;
	char	**new;
	int		j;

	count = 0;
	while (env[count])
		count++;
	i = -1;
	while (export[++i])
		count++;
	new = malloc(sizeof(char *) * count);
	i = -1;
	while (env[++i])
		new[i] = ft_strdupp(env[i]);
	j = -1;
	while (export[++j])
		new[i++] = ft_strdupp(export[j]);
	ft_export_cmp(new, count);
	ft_write_export(new, count);
	ft_free_export(new, count);
}

static void	ft_add_export(char **cmd, char **export, char **env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if ((cmd[i][0] >= 'A' && cmd[i][0] <= 'Z') \
			|| (cmd[i][0] >= 'a' && cmd[i][0] <= 'z') \
			|| cmd[i][0] == '_')
			ft_insert(export, cmd[i], env);
		else
			printf("export: %c%s\'%s\n", 96, cmd[i], ERR_EXPORT);
		i++;
	}
}

void	ft_export(char **cmd, char **env, char **export)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	if (count == 1)
		ft_sort_export(env, export);
	else
		ft_add_export(cmd, export, env);
}
