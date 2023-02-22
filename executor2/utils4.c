#include "executor.h"

int	ft_strcmpp(char *s1, char *s2, int size)
{
	int	i;

	i = 0;
	if (ft_strlenn(s1) - 1 != ft_strlenn(s2))
		return (0);
	while (i < size - 1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
