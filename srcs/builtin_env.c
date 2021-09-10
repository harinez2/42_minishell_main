#include "main.h"

static int	print_env_env(t_env *envlst, t_arg *arg, t_cmd *cmd)
{
	t_env		*e;

	e = envlst;
	if (!e)
	{
		print_perror(ENOENT, cmd->param[0], NULL);
		return (MASK_7BIT);
	}
	while (e != NULL)
	{
		if (e->value)
			printf("%s=%s\n", e->env, e->value);
		else if (arg->dbg)
			printf(COL_TX_CYAN"%s\n"COL_TX_RESET, e->env);
		e = e->next;
	}
	return (0);
}

int	builtincmd_env(t_arg *arg, t_cmd *cmd)
{
	int		ret;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd env ===\n");
	ret = print_env_env(arg->envlst, arg, cmd);
	if (arg->dbg)
	{
		printf(COL_TX_CYAN"\nshell envs:\n");
		if (arg->shellenvlst != NULL)
			print_env_env(arg->shellenvlst, arg, cmd);
		printf(COL_TX_RESET);
	}
	return (ret);
}
