#include "main.h"

void	builtincmd_echo(t_arg *arg, t_cmd *cmd)
{
	int		i;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd echo ===\n");
	i = 1;
	while (cmd->param[i] != NULL)
		printf("%s ", cmd->param[i++]);
	printf("\n");
}
