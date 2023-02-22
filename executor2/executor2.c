#include "executor.h"

int	ft_chk_io_file(t_cmd *cmd, int *ex_s)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strlen_c2d(tmp->i_tab) != ft_strlen_i(tmp->sign_i) ||
			ft_strlen_c2d(tmp->o_tab) != ft_strlen_i(tmp->sign_o))
		{
			printf("syntax error near unexpected token\n");
			*ex_s = 258;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}