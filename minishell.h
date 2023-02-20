/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:11:47 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/17 03:18:20 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <errno.h>
// # include <term.h>
# include "executor/executor.h"
# include "g_n_l/g_n_l.h"
# include "libft/libft.h"

# define SINGLE 1
# define DOUBLE 2
# define RE_INPUT 4
# define RE_OUTPUT 5
# define PROMPT "minishell start here > "
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define CLEAR "\033[0m"

typedef struct s_env
{
	char	**tmp_env;
	char	**export;
}	t_env;

typedef struct s_envargetter
{
	int		j;
	char	*evchar;
	int		k;
}	t_envargetter;

typedef struct s_parinsert
{
	int	i;
	int	j;
	int	k;
	int	l;
}	t_parinsert;

typedef struct s_lex
{
	int			cindex;
	char		*trimstr;
	char		*allstr;
	char		**lexed;
	char		***lextable;
	int			qmode;
}	t_lex;

typedef struct s_par
{
	char			**cmd;
	char			**i_tab;
	char			**o_tab;
	struct s_par	*next;
	struct s_par	*prev;
}	t_par;

typedef struct s_decor
{
	char	*pmptclr;
	char	*inpclr;
	char	*pmptstr;
	char	*pmptfull;
	char	*fullpmt;
}	t_decor;

typedef struct s_intvar
{
	int	q;
	int	st;
	int	ed;
	int	i;
	int	m;
	int	n;
}	t_intvar;

typedef struct s_exp
{
	char			**envar;
	char			**fullvar;
	char			**i_tab;
	char			**full_i;
	char			**o_tab;
	char			**full_o;
	struct s_exp	*next;
	struct s_exp	*prev;
}	t_exp;

typedef struct s_cmd
{
	char			**cmd;
	char			*pth;
	char			**i_tab;
	int				*sign_i;
	char			**o_tab;
	int				*sign_o;
	int				in_count;
	int				out_count;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_shell
{
	t_lex	*lex;
	t_par	*par;
	t_decor	*decor;
	t_exp	*exp;
	t_cmd	*tcmd;
}	t_shell;

// executor
void	ft_close_parent(t_data *data, int loop);
void	ft_executor(t_cmd *cmd, t_env *env, int *ex_s);
// executor_utils
void	ft_serch_path(t_data *data, t_env *env);
int		ft_count_cmd(t_cmd *cmd);
// executor_utils_2
void	ft_set_pipe(t_pipe *pipe, t_data *data, t_cmd *cmd, int loop);

// shdec
char	*ft_promptstart(int mode);
void	ft_avjoin(char *av, int mode, t_shell *shell);
void	ft_promptpare(int ac, char **av, t_shell *shell);
// sub_main
int		ft_submain(t_shell *shell, char **env);
// lexor
int		ft_lexmain(t_shell *shell, int start, int len);
// lexor_utils
int		ft_isspace(int c);
int		ft_isarrowpipe(int c);
int		ft_isquote(int c);
int		ft_issymbol(int c, char sym);
void	ft_nextlex_init(t_intvar *inv, int start, int *e, t_lex *tall);
// error checking
int		ft_chkandgo(t_lex *lex);
int		ft_isclosequote(t_lex *lex);
int		ft_triplearrow(t_lex *lex);
int		ft_triplepipe(t_lex *lex);
// parser
int		ft_parser(t_shell *shell);
int		ft_choosecount(char	**lex, char a);
int		ft_strstrlen(char **str);
// parser_utils
t_par	*ft_parini(t_shell *shell, int i);
void	ft_parinsert(t_par *par, t_cmd *tcmd, char **str);
t_cmd	*ft_cmdmaker(t_shell *shell);
t_cmd	*ft_tcmdini(t_shell *shell, int i);
// parser_utils2
void	ft_instcmdtopar(t_shell *shell, t_par *par, int ststlen, int j);
void	ft_parinsert2(char **str, t_parinsert *tmp, t_par *par, t_cmd *tcmd);
void	ft_parinsert_init(t_parinsert *tmp, char **str);
// expander c
char	*ft_envcompare(char *str, char **env);
char	*ft_putpath(char **cmd, char **envar, char **fullvar, int i);
// expander_utils
char	*ft_envargetter(char **cmd, int i);
int		ft_expander(t_shell *shell, char **env);
// expander_utils2
int		ft_exptostr(t_shell *shell);
// expanderutil
t_exp	*ft_expini(t_shell *shell);
t_exp	*ft_expmaker(t_shell *shell);
// free
void	ft_free2(char ***dptr);
void	ft_freeexp(t_shell	*shell);
void	ft_freepar(t_shell *shell);
void	ft_freetcmd(t_shell *shell);
t_cmd	*ft_finini(t_shell *shell);
t_cmd	*ft_finmaker(t_shell *shell);
// signal
void	ft_signals(void);
void	ft_handler(int signo, siginfo_t *s, void *old);

#endif
