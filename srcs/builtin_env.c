#include "main.h"

static void	print_env_env(t_arg *arg)
{
	t_env		*e;

	e = arg->envlst;
	while (e != NULL)
	{
		if (e->value)
			printf("%s=%s\n", e->env, e->value);
		e = e->next;
	}
}

void	builtincmd_env(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd env ===\n");
	print_env_env(arg);
}
