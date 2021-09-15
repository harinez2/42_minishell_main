#include "main.h"

static int	cd_chdir_multiple_errorcase(
	t_arg *arg, char *dest_fullpath, int getcwd_ret)
{
	putstr_stderr("cd: error retrieving current directory");
	putstr_stderr(": getcwd: cannot access parent directories: ");
	putstr_stderr(strerror(getcwd_ret));
	putstr_stderr("\n");
	update_pwd_envs(arg, dest_fullpath);
	return (1);
}

static int	cd_chdir(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	int		chdir_ret;
	int		getcwd_ret;
	char	*dest_fullpath;

	if (arg->dbg)
		printf("  previous pwd : %s\n", arg->pwd);
	if (arg->dbg)
		printf("  changing to  : %s\n", dest_path);
	chdir_ret = run_chdir(arg, cmd, dest_path, &dest_fullpath);
	if (chdir_ret == -2)
	{
		secure_free(dest_fullpath);
		return (1);
	}
	getcwd_ret = update_pwd_with_getcwd(&dest_fullpath);
	if (chdir_ret != 0 && getcwd_ret != 0)
		return (cd_chdir_multiple_errorcase(arg, dest_fullpath, getcwd_ret));
	else if (chdir_ret != 0)
	{
		secure_free(dest_fullpath);
		print_perror(chdir_ret, cmd->param[0], dest_path, arg);
		return (1);
	}
	update_pwd_envs(arg, dest_fullpath);
	return (0);
}

static int	cd_homedir(t_arg *arg, t_cmd *cmd)
{
	t_env	*e;

	e = arg->envlst;
	while (e != NULL)
	{
		if (ft_strncmp("HOME", e->env, 5) == 0)
		{
			if (arg->dbg)
				printf("  $HOME found  : %s\n", e->value);
			return (cd_chdir(arg, cmd, e->value));
		}
		e = e->next;
	}
	print_custom_error(ERR_HOME_NOT_SET, cmd->param[0], NULL, arg);
	return (1);
}

// no arg			move to $HOME dir
// other path		depends on chdir spec
int	builtincmd_cd(t_arg *arg, t_cmd *cmd)
{
	int		ret;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd cd ===\n");
	ret = 0;
	if (cmd->param_cnt == 1)
		ret = cd_homedir(arg, cmd);
	else
		ret = cd_chdir(arg, cmd, cmd->param[1]);
	return (ret);
}
