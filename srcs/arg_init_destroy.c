#include "main.h"

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
	arg->last_exit_status = 0;
	arg->dbg = 0;
}

void	update_envpath_with_environ(t_arg *arg)
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

void	destroy_path(t_arg *arg)
{
	int			i;

	i = 0;
	while (i < arg->path_cnt)
		secure_free(arg->path[i++]);
	arg->path_cnt = 0;
}

void	destroy_arg(t_arg *arg)
{
	secure_free(arg->read);
	destroy_path(arg);
	secure_free(arg->pwd);
	cmd_destroy(arg);
	destroy_envlst(arg);
}
