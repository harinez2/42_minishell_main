#include "main.h"

static void	cd_chdir(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	int		ret;
	char	*retcwd;
	char	currentpath[MAX_PATH];

	if (arg->dbg)
	{
		getcwd(currentpath, MAX_PATH);
		printf("  previous dir : %s\n", currentpath);
	}
	ret = chdir(dest_path);
	if (ret)
		print_perror(errno, cmd->param[0], dest_path);
	if (arg->dbg)
	{
		printf("  changing to  : %s\n", dest_path);
		printf("  chdir ret    : %d\n", ret);
	}
	if (ret)
		return ;
	retcwd = getcwd(currentpath, MAX_PATH);
	if (!retcwd)
		print_perror(errno, cmd->param[0], NULL);
	if (arg->dbg)
		printf("  current dir  : %s\n", currentpath);
}

static void	cd_homedir(t_arg *arg, t_cmd *cmd)
{
	t_env	*e;

	e = arg->envlst;
	while (e != NULL)
	{
		if (ft_strncmp("HOME", e->env, 5) == 0)
		{
			if (arg->dbg)
				printf("  $HOME found  : %s\n", e->value);
			cd_chdir(arg, cmd, e->value);
			return ;
		}
		e = e->next;
	}
	print_custom_error(ERR_HOME_NOT_SET, cmd->param[0], NULL);
}

// no arg			move to $HOME dir
// other path		depends on chdir spec
void	builtincmd_cd(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd cd ===\n");
	if (cmd->param_cnt == 1)
		cd_homedir(arg, cmd);
	else
		cd_chdir(arg, cmd, cmd->param[1]);
}
