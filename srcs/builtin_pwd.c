#include "main.h"

void	builtincmd_pwd(t_arg *arg, t_cmd *cmd)
{
	char	path[MAX_PATH];

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd pwd ===\n");
	getcwd(path, MAX_PATH);
	printf("%s\n", path);
}
