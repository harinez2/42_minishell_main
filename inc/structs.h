#ifndef STRUCTS_H
# define STRUCTS_H

// typedef struct	s_param
// {
// 	char			*p;
// 	struct s_param	*next;
// }	t_param;

typedef struct	s_cmd
{
	struct s_cmd	*next;
	char			*cmd;
	char			*param[MAX_ARGNUM];
	int				param_cnt;
	int				nxtcmd_relation;
	char			**redir_in;
	char			**redir_out;
}	t_cmd;

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*path[MAX_PATH];
	int		path_cnt;
	t_cmd	*cmdlst;
	int		dbg;
}	t_arg;

#endif
