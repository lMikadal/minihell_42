#include "executor.h"

int	ft_strlenn(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strlen_c2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpyy(void *dst, void *src, int n)
{
	int	i;

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
	int		len;
	char	*m;

	len = ft_strlenn(s1);
	m = (char *)malloc((len * sizeof(char)) + 1);
	if (m == NULL)
		return (0);
	ft_memcpyy(m, s1, len);
	m[len] = '\0';
	return (m);
}