#include "main.h"

static void	print_env_env(t_env *envlst, t_arg *arg)
{
	t_env		*e;

	e = envlst;
	while (e != NULL)
	{
		if (e->value)
			printf("%s=%s\n", e->env, e->value);
		else if (arg->dbg)
			printf(COL_TX_CYAN"%s\n"COL_TX_RESET, e->env);
		e = e->next;
	}
}

int	builtincmd_env(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd env ===\n");
	print_env_env(arg->envlst, arg);
	if (arg->dbg)
	{
		printf(COL_TX_CYAN"\nshell envs:\n");
		print_env_env(arg->shellenvlst, arg);
		printf(COL_TX_RESET);
	}
	return (0);
}
