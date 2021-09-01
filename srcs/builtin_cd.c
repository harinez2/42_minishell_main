#include "main.h"

static void	cd_chdir(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	int		ret;
	char	currentpath[MAX_PATH];

	if (arg->dbg)
	{
		getcwd(currentpath, MAX_PATH);
		printf("  previous dir : %s\n", currentpath);
	}
	ret = chdir(dest_path);
	if (arg->dbg)
	{
		printf("  changing to  : %s\n", dest_path);
		printf("  chdir ret    : %d\n", ret);
		getcwd(currentpath, MAX_PATH);
		printf("  current dir  : %s\n", currentpath);
	}
	if (ret)
		print_error(ERR_CD_INVALIDPATH, cmd->param[0], dest_path);
}

static void	cd_homedir(t_arg *arg, t_cmd *cmd)
{
	t_env	*e;

	e = arg->envlst;
	while (e != NULL)
	{
		if (ft_strncmp("HOME", e->env, 5) == 0)
		{
			printf("  $HOME found: %s\n", e->value);
			cd_chdir(arg, cmd, e->value);
			return ;
		}
		e = e->next;
	}
}

// no arg			move to $HOME dir
// relative path	depends on chdir spec
void	builtincmd_cd(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd cd ===\n");
	if (cmd->param_cnt == 1)
		cd_homedir(arg, cmd);
	else
		cd_chdir(arg, cmd, cmd->param[1]);
}
