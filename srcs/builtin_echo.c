#include "main.h"

void	builtincmd_echo(t_arg *arg, t_cmd *cmd)
{
	if (arg->dbg == 1)
		printf("<<< builtin cmd echo >>>\n");
	printf("%s\n", cmd->param[1]);
}
