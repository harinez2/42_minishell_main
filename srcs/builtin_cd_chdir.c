#include "main.h"

static int	generate_fullpath(
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

static void	reduce_samedirchar(char *path, char *new_path)
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
		else
			new_path[new_i++] = path[i++];
	}
	new_path[new_i] = '\0';
}

static int	reduce_relativedirchar(char *new_path)
{
	int		i;
	int		new_i;

	i = 0;
	new_i = 0;
	while (new_path[i])
	{
		if (new_path[i] == '/' && new_path[i + 1] == '.'
			&& new_path[i + 2] == '.'
			&& (new_path[i + 3] == '/' || new_path[i + 3] == '\0'))
		{
			i += 3;
			while (new_i > 0 && new_path[--new_i] != '/')
				;
		}
		else
			new_path[new_i++] = new_path[i++];
	}
	new_path[new_i] = '\0';
	return (new_i);
}

static char	*resolve_relative_path(char *path)
{
	char	*new_path;
	char	*ret;
	int		new_i;

	new_path = ft_strdup(path);
	reduce_samedirchar(path, new_path);
	new_i = reduce_relativedirchar(new_path);
	new_path[new_i] = '\0';
	ret = ft_strdup(new_path);
	secure_free(new_path);
	return (ret);
}

int	run_chdir(
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
