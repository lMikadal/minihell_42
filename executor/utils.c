/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:30:45 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/11 00:00:41 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlenn(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmpp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (ft_strlenn(s2) == 0)
		return (1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_word(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word++;
		i++;
	}
	return (word);
}

char	*ft_loc_string(char *s, int start, int end)
{
	char	*m;
	int		i;

	i = 0;
	m = (char *)malloc((end - start + 1) * sizeof(char));
	if (m == NULL)
		return (0);
	while (start < end)
		m[i++] = s[start++];
	m[i] = '\0';
	return (m);
}

char	**ft_splitt(char *s, char c)
{
	char	**m;
	int		i;
	int		start;
	int		word;

	if (s == NULL)
		return (0);
	m = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (m == NULL)
		return (0);
	i = 0;
	word = 0;
	while (i <= ft_strlenn(s))
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if (i != 0 && s[i - 1] != c && (s[i] == c || s[i] == '\0'))
			m[word++] = ft_loc_string(s, start, i);
		i++;
	}
	m[word] = 0;
	return (m);
}
