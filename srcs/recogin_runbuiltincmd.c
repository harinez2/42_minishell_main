#include "main.h"

int	run_builtincmd(char *read, t_arg *arg)
{
	if (ft_strncmp("echo", read, 5) == 0)
		builtincmd_echo(arg, read);
	else if (ft_strncmp("export", read, 7) == 0)
		builtincmd_export(arg, arg->envp);
	else if (ft_strncmp("env", read, 4) == 0)
		builtincmd_env(arg);
	else if (ft_strncmp("pwd", read, 4) == 0)
		builtincmd_pwd(arg);
	else if (ft_strncmp("cd", read, 3) == 0)
		builtincmd_cd(arg, read);
	else
		return (0);
	return (1);
}
