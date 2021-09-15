#include "main.h"

int	builtincmd_exit(t_arg *arg, t_cmd *cmd)
{
	int		ret;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd exit ===\n");
	ret = 0;
	if (cmd->param_cnt > 1)
		ret = ft_atoi(cmd->param[1]);
	while (ret < 0)
		ret += 256;
	ret %= 256;
	if (arg->dbg)
		printf("Exit code:%d\n", ret);
	destroy_arg(arg);
	write(1, &"exit\n", 5);
	exit (ret);
}
