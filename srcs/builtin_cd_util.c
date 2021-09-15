#include "main.h"

int	generate_fullpath(
	t_arg *arg, t_cmd *cmd, char *dest_path, char **dest_fullpath)
{
	t_env	*e;

	if (dest_path[0] == '/')
		*dest_fullpath = ft_strdup(dest_path);
	else if (dest_path[0] == '~')
	{
		e = get_node_from_envlst(arg->envlst, "HOME");
		if (e)
			*dest_fullpath = ft_strjoin(e->value, dest_path + 1);
		else if (arg->initial_home)
			*dest_fullpath = ft_strjoin(arg->initial_home, dest_path + 1);
		else
		{
			print_custom_error(ERR_HOME_NOT_SET, cmd->param[0], NULL, arg);
			return (-2);
		}
	}
	else
	{
		if (arg->pwd[ft_strlen(arg->pwd) - 1] == '/')
			arg->pwd[ft_strlen(arg->pwd) - 1] = '\0';
		*dest_fullpath = ft_strjoin3(arg->pwd, "/", dest_path);
	}
	return (0);
}

static int	reduce_verbose_letter(
	char *path, char *new_path)
{
	int		i;
	int		new_i;

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
			while (new_i > 0 && new_path[new_i] != '/')
				new_i--;
		}
		else
			new_path[new_i++] = path[i++];
	}
	return (new_i);
}

char	*resolve_relative_path(char *path)
{
	char	*new_path;
	char	*ret;
	int		new_i;

	new_path = ft_strdup(path);
	new_i = reduce_verbose_letter(path, new_path);
	new_path[new_i] = '\0';
	ret = ft_strdup(new_path);
	secure_free(new_path);
	return (ret);
}

int	update_pwd_with_getcwd(char **dest_fullpath)
{
	char	currentpath[MAX_PATH_LEN];
	char	*retcwd;

	retcwd = getcwd(currentpath, MAX_PATH_LEN);
	if (!retcwd)
	{
		return (errno);
	}
	else
	{
		secure_free(*dest_fullpath);
		*dest_fullpath = ft_strdup(currentpath);
	}
	return (0);
}

void	update_pwd_envs(t_arg *arg, char *dest_fullpath)
{
	t_env	*pwd_node;

	secure_free(arg->pwd);
	arg->pwd = dest_fullpath;
	if (arg->dbg)
		printf("  pwd updated  : %s\n", arg->pwd);
	delete_env_from_envlst(&arg->envlst, "OLDPWD");
	pwd_node = get_node_from_envlst(arg->envlst, "PWD");
	if (pwd_node)
		push_back_envlst(&arg->envlst, ft_strdup("OLDPWD"),
			ft_strdup(pwd_node->value), arg);
	delete_env_from_envlst(&arg->envlst, "PWD");
	push_back_envlst(
		&arg->envlst, ft_strdup("PWD"), ft_strdup(dest_fullpath), arg);
	if (arg->dbg)
	{
		pwd_node = get_node_from_envlst(arg->envlst, "PWD");
		if (pwd_node)
			printf("  env PWD      : %s\n", pwd_node->value);
		pwd_node = get_node_from_envlst(arg->envlst, "OLDPWD");
		if (pwd_node)
			printf("  env OLDPWD   : %s\n", pwd_node->value);
	}
}
