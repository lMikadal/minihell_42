/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchiewli <rchiewli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:30:13 by pmikada           #+#    #+#             */
/*   Updated: 2023/02/18 15:25:26 by rchiewli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "g_n_l.h"

# define EXECUTOR_H
# define PATH "PATH="
# define PWD "PWD="
# define OLDPWD "OLDPWD="
# define HOME "HOME="

# define ERR_EXPORT ": not a valid identifier"
# define ERR_CMM ": command not found"
# define ERR_EXIT ": too many arguments"
# define ERR_EXIT_N ": numeric argument required"

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

typedef struct s_pipe
{
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
}	t_pipe;

typedef struct s_data
{
	char	**path;
	char	**env;
	int		ori_fd[2];
	int		**fd_pipe;
	int		count_cmd;
	int		*child_pid;
	int		*ex_s;
}	t_data;

// main
void	ft_print_env(char **env); // print **char
// executor
void	ft_executor(t_cmd *cmd, char **env, int	*ex_s);
// executor2
int		ft_chk_io_file(t_cmd *cmd, int *ex_s);
// executor_fork
void	ft_fork(t_cmd *cmd, t_data *data, int loop);
// executor_fork2
void	ft_close(t_data *data, int loop);
void	ft_close_parent(t_data *data, int loop);
void	ft_here_doc(t_pipe *p, t_cmd *cmd, int idx, int tmp);
// utils
int		ft_strlenn(char *s);
int		ft_strlen_c2d(char **s);
void	*ft_memcpyy(void *dst, void *src, int n);
char	*ft_strdupp(char *s1);
int		ft_strncmpp(char *s1, char *s2, int n);
// utils2
char	**ft_splitt(char *s, char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoinn(char *s1, char *s2);
// utils3
int		ft_strlen_i(int *s);
void	ft_strlcpyy(char *dst, char *src, int size);
char	*ft_itoaa(int n);
void	ft_strlcatt(char *dst, char *src, int size);
// utils4
int		ft_strcmpp(char *s1, char *s2, int size);
// free
void	ft_free_c2d(char **s);
void	ft_free_i2d(int	**s, int size);
void	ft_free_data(t_data *data);
void	ft_free_pipe(t_pipe *pipe);

#endif
