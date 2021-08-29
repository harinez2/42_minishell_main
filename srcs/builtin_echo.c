#include "main.h"

void	builtincmd_echo(t_arg *arg, t_cmd *cmd)
{
	int		i;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd echo ===\n");
	i = 1;
	while (1)
	{
		printf("%s", cmd->param[i]);
		i++;
		if (cmd->param[i] == NULL)
			break ;
		printf(" ");
	}
	printf("\n");
}
