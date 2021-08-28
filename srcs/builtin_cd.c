#include "main.h"

void	builtincmd_cd(t_arg *arg, t_cmd *cmd)
{
	int		ret;

	if (arg->dbg == 1)
		printf("<<< builtin cmd cd >>>\n");
	ret = chdir(cmd->param[1]);
	if (ret)
		print_error(ERR_CD_INVALIDPATH, cmd->param[1]);
	if (arg->dbg == 1)
		builtincmd_pwd(arg);
}
