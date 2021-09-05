#include "main.h"

void	builtincmd_pwd(t_arg *arg, t_cmd *cmd)
{
	char	path[MAX_PATH];
	char	*ret;
	t_env	*pwd;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd pwd ===\n");
	ret = getcwd(path, MAX_PATH);
	if (ret)
	{
		printf("%s\n", path);
		return ;
	}
	pwd = get_node_from_envlst(arg->envlst, "PWD");
	if (pwd)
	{
		printf("%s\n", pwd->value);
		return ;
	}
	print_perror_exit(errno, cmd->param[0], NULL, arg);
}
