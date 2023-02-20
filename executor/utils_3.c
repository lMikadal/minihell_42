/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmikada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:32:26 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 00:32:27 by pmikada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpyy(void *dst, void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strdupp(char *s1)
{
	size_t	len;
	char	*m;

	len = ft_strlenn(s1);
	m = (char *)malloc((len * sizeof(char)) + 1);
	if (m == NULL)
		return (0);
	ft_memcpyy(m, s1, len);
	m[len] = '\0';
	return (m);
}

int	ft_strcmp_ori(char *s1, char *s2)
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

int	ft_strlen_2(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=' && s[i])
		i++;
	return (i);
}

void	ft_print_exit(char **cmd)
{
	int	j;

	j = -1;
	while (cmd[1][++j])
	{
		if (ft_isdigit(cmd[1][j]) == 0)
		{
			printf("exit: %s%s\n", cmd[1], ERR_EXIT_N);
			exit (255);
		}
	}
}
