#include "main.h"

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
