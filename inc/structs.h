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
	char			*redir_in;
	char			*redir_out;
}	t_cmd;

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*path[MAX_PATH];
	int		path_cnt;
	t_cmd	*cmdlst;
	t_env	*envlst;
	int		dbg;
}	t_arg;

#endif
