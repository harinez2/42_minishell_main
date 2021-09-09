#include "main.h"

int	builtincmd_pwd(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd pwd ===\n");
	printf("%s\n", arg->pwd);
	return (0);
}
