#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*param[MAX_ARGNUM];
	int				param_cnt;
	int				nxtcmd_relation;
	int				pipe[2];
	char			*redir_in;
	char			*redir_out;
	int				prev_type;//will be deleted
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
