#include "main.h"

static void	update_pwd_with_getcwd(t_arg *arg)
{
	char	currentpath[MAX_PATH];
	// char	*currentpath;
	char	*retcwd;
	int		err_no;

	// currentpath = NULL;
	retcwd = getcwd(currentpath, MAX_PATH);
	if (!retcwd)
	{
		err_no = errno;
		putstr_stderr(": getcwd: cannot access parent directories: ");
		putstr_stderr(strerror(err_no));
		putstr_stderr("\n");
	}
	else
	{
		secure_free(arg->pwd);
		arg->pwd = ft_strdup(currentpath);
	}
	if (arg->dbg)
		printf("  new pwd      : %s\n", arg->pwd);
	// secure_free(currentpath);
}

static void	update_env_pwd(t_arg *arg)
{
	t_env	*pwd_node;

	delete_env_from_envlst(&arg->envlst, "OLDPWD");
	pwd_node = get_node_from_envlst(arg->envlst, "PWD");
	if (pwd_node)
		push_back_envlst(&arg->envlst, ft_strdup("OLDPWD"), ft_strdup(pwd_node->value), arg);
	delete_env_from_envlst(&arg->envlst, "PWD");
	push_back_envlst(&arg->envlst, ft_strdup("PWD"), ft_strdup(arg->pwd), arg);
	if (arg->dbg)
	{
		pwd_node = get_node_from_envlst(arg->envlst, "OLDPWD");
		if (pwd_node)
			printf("  env          : OLDPWD = %s\n", pwd_node->value);
		pwd_node = get_node_from_envlst(arg->envlst, "PWD");
		if (pwd_node)
			printf("  env          : PWD    = %s\n", pwd_node->value);
	}
}

char	*resolve_relative_path(char *path)
{
	char	*new_path;
	char	*ret;
	int		new_i;
	int		i;

	new_path = ft_strdup(path);
	i = 0;
	new_i = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] == '/')
			i++;
		else if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '/')
			i += 2;
		else if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.'
			&& (path[i + 3] == '/' || path[i + 3] == '\0'))
		{
			i += 3;
			while (new_i >= 0 && new_path[--new_i] != '/')
				;
		}
		else
			new_path[new_i++] = path[i++];
	}
	new_path[new_i] = '\0';
	ret = ft_strdup(new_path);
	secure_free(new_path);
	return (ret);
}

static void	cd_chdir(t_arg *arg, t_cmd *cmd, char *dest_path)
{
	char	*tmppath;
	int		ret;
	t_env	*e;

	if (arg->dbg)
	{
		printf("  previous pwd : %s\n", arg->pwd);
		printf("  changing to  : %s\n", dest_path);
	}
	tmppath = arg->pwd;
	if (dest_path[0] == '/')
	{
		arg->pwd = ft_strdup(dest_path);
		ret = chdir(arg->pwd);
	}
	else if (dest_path[0] == '~')
	{
		e = get_node_from_envlst(arg->envlst, "HOME");
		if (!e)
		{
			print_custom_error(ERR_HOME_NOT_SET, cmd->param[0], NULL);
			return ;
		}
		arg->pwd = ft_strjoin(e->value, dest_path + 1);
		ret = chdir(arg->pwd);
	}
	else
	{
		arg->pwd = ft_strjoin3(tmppath, "/", dest_path);
		ret = chdir(arg->pwd);
	}
	if (ret == -1)
	{
		secure_free(tmppath);
		tmppath = resolve_relative_path(arg->pwd);
		ret = chdir(tmppath);
		if (ret == -1)
			putstr_stderr("cd: error retrieving current directory");
	}
	secure_free(tmppath);
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
