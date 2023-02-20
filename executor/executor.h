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
# define EXECUTOR_H
# define PATH "PATH="
# define PWD "PWD="
# define OLDPWD "OLDPWD="
# define HOME "HOME="

# define ERR_EXPORT ": not a valid identifier"
# define ERR_CMM ": command not found"
# define ERR_EXIT ": too many arguments"
# define ERR_EXIT_N ": numeric argument required"

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

// executor_utils
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_set_ori_fd(t_data *data);
void	ft_init_pipe(t_data *data);
// executor_utils_2
char	*ft_strjoinn(char *s1, char *s2);
// executor_utils_3
int		ft_chk_str(char *cmd);
void	ft_chk_child(t_pipe *pipe, t_data *data);
void	ft_chk_parent(t_pipe *pipe, t_data *data, int *ex_s);
// utils
int		ft_strlenn(char *s);
int		ft_strncmpp(char *s1, char *s2, int n);
int		ft_count_word(char *s, char c);
char	*ft_loc_string(char *s, int start, int end);
char	**ft_splitt(char *s, char c);
// utils_2
void	ft_strlcatt(char *dst, char *src, int size);
void	ft_strlcpyy(char *dst, char *src, int size);
char	*ft_itoaa(int n);
int		ft_strcmpp(char *s1, char *s2, int size);
// utils_3
void	*ft_memcpyy(void *dst, void *src, size_t n);
char	*ft_strdupp(char *s1);
int		ft_strcmp_ori(char *s1, char *s2);
int		ft_strlen_2(char *s);
void	ft_print_exit(char **cmd);
// free
void	ft_free_st(t_data *data);
void	ft_free_ch_2d(char **s);
void	ft_free_int_2d(int **s, int size);
void	ft_free_export(char **new, int count);
// builtins.c
void	ft_echo(char **cmd);
void	ft_cd(char *path, char ***env);
void	ft_pwd(void);
void	ft_env(char **env);
int		ft_exit(char **cmd);
// builtins_2.c
void	ft_export(char **cmd, char **env, char **export);
// builtins_3.c
void	ft_insert(char **export, char *s, char **env);
void	ft_unset(char **cmd, char **export, char **env);
void	ft_exit_status(int *ex_s);
void	ft_in_parent(t_pipe *pipe, int *ex_s, t_data *data, int loop);

#endif
