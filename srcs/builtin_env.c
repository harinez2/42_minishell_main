#include "main.h"

void	builtincmd_env(t_arg *arg, t_cmd *cmd)
{
	t_env		*e;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd env ===\n");
	e = arg->envlst;
	while (e != NULL)
	{
		printf("%s=%s\n", e->env, e->value);
		e = e->next;
	}
}
