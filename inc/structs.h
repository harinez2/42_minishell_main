/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:41 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:42:42 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	struct s_env	*next;
	char			*env;
	char			*value;
}	t_env;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*param[MAX_ARGNUM];
	int				param_cnt;
	int				nxtcmd_relation;
	int				pipe[2];
	int				heredoc_flg;
	char			*redir_in;
	int				append_flg[MAX_ARGNUM];
	char			*redir_out[MAX_ARGNUM];
	int				redir_out_cnt;
}	t_cmd;

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*read;
	char	*path[MAX_PATH_CNT];
	int		path_cnt;
	t_cmd	*cmdlst;
	t_env	*envlst;
	t_env	*shellenvlst;
	char	*pwd;
	char	*initial_home;
	int		last_exit_status;
	int		dbg;
}	t_arg;

#endif
