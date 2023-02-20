/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmikada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 03:50:56 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/19 03:50:58 by pmikada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_tmp_env(t_env *tmp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	tmp->tmp_env = malloc(sizeof(char *) * (i + 1));
	if (tmp->tmp_env == NULL)
		return ;
	i = -1;
	while (env[++i])
		tmp->tmp_env[i] = ft_strdupp(env[i]);
	tmp->tmp_env[i] = NULL;
	tmp->export = malloc(sizeof(char *) * 100);
}

static void	ft_free_sub(t_shell *shell)
{
	int	x;

	x = -1;
	while (shell->lex->lextable[++x])
		free(shell->lex->lextable[x]);
	free(shell->lex->lextable);
	free(shell->lex->trimstr);
	ft_freepar(shell);
	ft_freeexp(shell);
	ft_freetcmd(shell);
}

static void	ft_submain2(t_shell *shell, t_env *tmp_env, int *exit_s)
{
	int	len;

	len = 0;
	add_history(shell->lex->allstr);
	shell->lex->trimstr = ft_strtrim(shell->lex->allstr, " ");
	len = ft_strlen(shell->lex->trimstr);
	ft_lexmain(shell, 0, len);
	ft_parser(shell);
	ft_expander(shell, tmp_env->tmp_env);
	ft_exptostr(shell);
	ft_executor(shell->tcmd, tmp_env, exit_s);
	ft_free_sub(shell);
}

int	ft_submain(t_shell *shell, char **env)
{
	t_env	tmp_env;
	int		exit_s;

	shell->lex = malloc(sizeof(t_lex));
	ft_tmp_env(&tmp_env, env);
	exit_s = 0;
	while (1)
	{
		shell->lex->lexed = malloc(sizeof(char *) * 1000);
		if (shell->lex->lexed == NULL)
			return (0);
		shell->lex->allstr = readline(shell->decor->pmptfull);
		if (shell->lex->allstr == NULL)
		{
			free(shell->lex->allstr);
			return (0);
		}
		if (ft_strlen(shell->lex->allstr) > 0)
			ft_submain2(shell, &tmp_env, &exit_s);
		free(shell->lex->lexed);
		free(shell->lex->allstr);
	}
	return (0);
}
