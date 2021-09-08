#include "main.h"

static int	update_pwd(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	char	*tmppath;
	t_env	*e;

	tmppath = arg->pwd;
	if (dest_path[0] == '/')
		arg->pwd = ft_strdup(dest_path);
	else if (dest_path[0] == '~')
	{
		e = get_node_from_envlst(arg->envlst, "HOME");
		if (!e)
		{
			print_custom_error(ERR_HOME_NOT_SET, cmd->param[0], NULL);
			return (-1);
		}
		arg->pwd = ft_strjoin(e->value, dest_path + 1);
	}
	else
		arg->pwd = ft_strjoin3(tmppath, "/", dest_path);
	secure_free(tmppath);
	return (0);
}

static void	run_chdir(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	char	*tmppath;
	int		ret;

	if (update_pwd(arg, cmd, dest_path) == -1)
		return ;
	ret = chdir(arg->pwd);
	if (ret == -1)
	{
		tmppath = resolve_relative_path(arg->pwd);
		ret = chdir(tmppath);
		if (ret == -1)
			putstr_stderr("cd: error retrieving current directory");
		secure_free(tmppath);
	}
}

static void	cd_chdir(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	if (arg->dbg)
	{
		printf("  previous pwd : %s\n", arg->pwd);
		printf("  changing to  : %s\n", dest_path);
	}
	run_chdir(arg, cmd, dest_path);
	update_pwd_with_getcwd(arg);
	update_env_pwd(arg);
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
