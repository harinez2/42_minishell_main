#include "main.h"

void	builtincmd_env(t_arg *arg, t_cmd *cmd)
{
	extern char	**environ;
	int			i;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd env ===\n");
	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
}
