/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmikada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:18 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/20 10:59:30 by pmikada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strncmpp(cmd[1], "-n", 2) == 0)
		i = 1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if ((cmd[i][0] == '\'' || cmd[i][0] == '\"') && cmd[i][j] == '\\')
				printf("%c", cmd[i][j]);
			else if ((cmd[i][0] != '\'' || cmd[i][0] != '\"') \
				&& cmd[i][j] == '\\')
				continue ;
			else if (cmd[i][j] != '\"' && cmd[i][j] != '\'')
				printf("%c", cmd[i][j]);
		}
		if (cmd[i + 1] != NULL)
			printf(" ");
	}
	if (ft_strncmpp(cmd[1], "-n", 2) == 1)
		printf("\n");
}

void	ft_cd(char *path, char ***env)
{
	int		i;

	if (path == NULL || path[0] == '\0' || path[0] == '~')
	{
		i = 0;
		while (ft_strncmpp(HOME, env[0][i], 5))
			i++;
		chdir(&env[0][i][5]);
	}
	else
		chdir(path);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1000);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

int	ft_exit(char **cmd)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i >= 2)
	{
		ft_print_exit(cmd);
		if (i == 2)
			exit (ft_atoi(cmd[1]));
		else
		{
			printf("exit: %s\n", ERR_EXIT);
			return (1);
		}
	}
	return (0);
}
