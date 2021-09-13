#include "main.h"

static int	run_chdir(
	t_arg *arg, t_cmd *cmd, char *dest_path, char	**dest_fullpath)
{
	char	*tmppath;
	int		ret;

	if (generate_fullpath(arg, cmd, dest_path, dest_fullpath) == -2)
		return (-2);
	ret = chdir(*dest_fullpath);
	if (ret == -1)
	{
		tmppath = resolve_relative_path(*dest_fullpath);
		ret = chdir(tmppath);
		if (ret == -1)
			ret = errno;
		secure_free(tmppath);
	}
	return (ret);
}

static void	print_non_existing_path_error(int getcwd_ret)
{
	putstr_stderr("cd: error retrieving current directory");
	putstr_stderr(": getcwd: cannot access parent directories: ");
	putstr_stderr(strerror(getcwd_ret));
	putstr_stderr("\n");
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
		return (1);
	getcwd_ret = update_pwd_with_getcwd(&dest_fullpath);
	if (chdir_ret != 0)
	{
		if (getcwd_ret != 0)
		{
			print_non_existing_path_error(getcwd_ret);
			update_pwd_envs(arg, dest_fullpath);
		}
		else
			print_perror(chdir_ret, cmd->param[0], dest_path);
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
