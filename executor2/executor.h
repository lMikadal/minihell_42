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
	char	**export;
	int		ori_fd[2];
	int		**fd_pipe;
	int		count_cmd;
	int		*child_pid;
}	t_data;

// utils
int		ft_strlenn(char *s);
int		ft_strlen_c2d(char **s);
void	*ft_memcpyy(void *dst, void *src, int n);
char	*ft_strdupp(char *s1);
// free
void	ft_free_c2d(char **s);

#endif
