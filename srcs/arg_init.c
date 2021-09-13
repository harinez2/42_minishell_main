#include "main.h"

void	update_envpath(t_arg *arg, char *path_env)
{
	int			i;
	int			start_i;

	destroy_path(arg);
	i = 0;
	while (path_env[i] != '\0' && arg->path_cnt < MAX_PATH_CNT)
	{
		skip_whitespace(path_env, &i);
		start_i = i;
		while (path_env[i] != ':' && path_env[i] != '\0')
			i++;
		arg->path[arg->path_cnt++] = ft_substr(path_env, start_i, i - start_i);
		if (path_env[i] == ':')
			i++;
	}
	arg->path[arg->path_cnt] = NULL;
}

static void	update_envpath_with_environ(t_arg *arg)
{
	extern char	**environ;
	int			i;
	char		*path_env;

	path_env = NULL;
	i = 0;
	while (environ[++i] != NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			path_env = &environ[i][5];
	}
	if (path_env == NULL)
		return ;
	update_envpath(arg, path_env);
}

static void	update_shlvl(t_arg *arg)
{
	t_env	*e;
	char	*value;
	int		value_int;

	e = get_node_from_envlst(arg->envlst, "SHLVL");
	if (e != NULL)
	{
		value = ft_strdup(e->value);
		value_int = ft_atoi(value);
		value_int++;
		update_existing_env(
			&(arg->envlst), ft_strdup("SHLVL"), ft_itoa(value_int), arg);
		secure_free(value);
	}
}

void	init_arg(int argc, char **argv, char **envp, t_arg *arg)
{
	char		currentpath[MAX_PATH_LEN];

	arg->argc = argc;
	arg->argv = argv;
	arg->envp = envp;
	arg->read = NULL;
	arg->path_cnt = 0;
	update_envpath_with_environ(arg);
	arg->cmdlst = NULL;
	arg->envlst = NULL;
	arg->shellenvlst = NULL;
	arg->pwd = getcwd(currentpath, MAX_PATH_LEN);
	if (!arg->pwd)
		print_perror_exit(errno, "getcwd", NULL, arg);
	arg->pwd = ft_strdup(currentpath);
	init_envlst(arg);
	update_shlvl(arg);
	arg->initial_home
		= ft_strdup(get_node_from_envlst(arg->envlst, "HOME")->value);
	arg->last_exit_status = 0;
	arg->dbg = 0;
}
