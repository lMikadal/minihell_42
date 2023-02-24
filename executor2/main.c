#include "executor.h"

static void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	int		round = 1;

	tmp = cmd;
	while(tmp)
	{
		printf("round %d\n", round++);
		i = -1;
		while (tmp->cmd[++i])
			printf("cmd[%d] %s, ", i, tmp->cmd[i]);
		if (tmp->cmd[i] == NULL)
			printf("cmd[%d] NULL\n", i);
		i = -1;
		while (tmp->i_tab[++i])
			printf("i_tab[%d] %s, ", i, tmp->i_tab[i]);
		if (tmp->i_tab[i] == NULL)
			printf("i_tab[%d] NULL\n", i);
		i = -1;
		while (tmp->sign_i[++i] != 0)
			printf("sign_i[%d] %d, ", i, tmp->sign_i[i]);
		if (tmp->sign_i[i] == 0)
			printf("sign_i[%d] 0\n", i);
		i = -1;
		while (tmp->o_tab[++i])
			printf("o_tab[%d] %s, ", i, tmp->o_tab[i]);
		if (tmp->o_tab[i] == NULL)
			printf("o_tab[%d] NULL\n", i);
		i = -1;
		while (tmp->sign_o[++i] != 0)
			printf("sign_o[%d] %d, ", i, tmp->sign_o[i]);
		if (tmp->sign_o[i] == 0)
			printf("sign_o[%d] 0\n", i);
		printf("=====\n");
		tmp = tmp->next;
	}
}

void	ft_print_env(char **env)
{
	int	i;

	i = -1;
	if (env == NULL)
	{
		printf("this NULL\n");
		return ;
	}
	while (env[++i])
		printf("%s\n", env[i]);
	printf("=====\n");
}

static void	ft_tmp_env(char ***tmp, char **env)
{
	int	len;
	int	i;

	len = ft_strlen_c2d(env);
	tmp[0] = malloc(sizeof(char *) * (len + 1));
	if (tmp[0] == NULL)
		return ;
	i = -1;
	while (env[++i])
		tmp[0][i] = ft_strdupp(env[i]);
	tmp[0][i] = NULL;
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_cmd	cmd1;
	// t_cmd	cmd2;
	int		ex_s = 1;
	char	**tmp_env = NULL;

	char *cmdd[] = {"unset", "NAME", "=", NULL};
	char *i_tabb[] = {NULL};
	int sign_ii[] = {0};
	char *o_tabb[] = {NULL};
	int sign_oo[] = {0};
	cmd1.cmd = (char **)cmdd;
	cmd1.i_tab = (char **)i_tabb;
	cmd1.sign_i = (int *)sign_ii;
	cmd1.o_tab = (char **)o_tabb;
	cmd1.sign_o = (int *)sign_oo;
	cmd1.next = NULL;
	
	// char *cmdd2[] = {"grep", "executor", NULL};
	// char *i_tabb2[] = {NULL};
	// int sign_ii2[] = {0};
	// char *o_tabb2[] = {"t.txt", NULL};
	// int sign_oo2[] = {2, 0};
	// cmd2.cmd = (char **)cmdd2;
	// cmd2.i_tab = (char **)i_tabb2;
	// cmd2.sign_i = (int *)sign_ii2;
	// cmd2.o_tab = (char **)o_tabb2;
	// cmd2.sign_o = (int *)sign_oo2;
	// cmd2.next = NULL;
	
ft_print_cmd(&cmd1);
	ft_tmp_env(&tmp_env, env);
	ft_executor(&cmd1, tmp_env, &ex_s);
printf("exit_status %d\n", ex_s);
	return (0);
}