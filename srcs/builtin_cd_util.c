#include "main.h"

static int	reduce_verbose_letter(
	char *path, int *i, char *new_path, int *new_i)
{
	if (path[*i] == '/' && path[*i + 1] == '/')
		(*i)++;
	else if (path[*i] == '/' && path[*i + 1] == '.' && path[*i + 2] == '/')
		*i += 2;
	else if (path[*i] == '/' && path[*i + 1] == '.' && path[*i + 2] == '.'
		&& (path[*i + 3] == '/' || path[*i + 3] == '\0'))
	{
		*i += 3;
		while (*new_i >= 0 && new_path[--(*new_i)] != '/')
			;
	}
	else
		return (0);
	return (1);
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
		if (reduce_verbose_letter(path, &i, new_path, &new_i) == 1)
			;
		else
			new_path[new_i++] = path[i++];
	}
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

void	update_pwd_envs(t_arg *arg, char *path)
{
	t_env	*pwd_node;

	secure_free(arg->pwd);
	arg->pwd = path;
	if (arg->dbg)
		printf("  pwd updated  : %s\n", arg->pwd);
	delete_env_from_envlst(&arg->envlst, "OLDPWD");
	pwd_node = get_node_from_envlst(arg->envlst, "PWD");
	if (pwd_node)
		push_back_envlst(&arg->envlst, ft_strdup("OLDPWD"),
			ft_strdup(pwd_node->value), arg);
	delete_env_from_envlst(&arg->envlst, "PWD");
	push_back_envlst(&arg->envlst, ft_strdup("PWD"), ft_strdup(path), arg);
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
