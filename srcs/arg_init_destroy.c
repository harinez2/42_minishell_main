#include "main.h"

void	init_arg(int argc, char **argv, char **envp, t_arg *arg)
{
	char	currentpath[MAX_PATH];

	arg->argc = argc;
	arg->argv = argv;
	arg->envp = envp;
	arg->read = NULL;
	arg->path_cnt = 0;
	update_envpath(arg);
	arg->cmdlst = NULL;
	arg->envlst = NULL;
	arg->shellenvlst = NULL;
	arg->pwd = getcwd(currentpath, MAX_PATH);
	if (!arg->pwd)
		print_perror_exit(errno, "getcwd", NULL, arg);
	arg->pwd = ft_strdup(currentpath);
	init_envlst(arg);
	arg->last_exit_status = 0;
	arg->dbg = 0;
}

void	update_envpath(t_arg *arg)
{//TODO:update
	int			i;
	extern char	**environ;

	if (arg->path_cnt)
		secure_free(arg->path[0]);
	i = -1;
	arg->path_cnt = 0;
	while (environ[++i] != NULL)
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			arg->path[arg->path_cnt++] = ft_strdup(&environ[i][5]);
	i = 0;
	while (arg->path[0][i] != '\0')
	{
		if (arg->path[0][i] == ':')
		{
			arg->path[0][i] = '\0';
			arg->path[arg->path_cnt++] = &arg->path[0][i + 1];
		}
		i++;
	}
	arg->path[arg->path_cnt] = NULL;
}

void	destroy_arg(t_arg *arg)
{
	secure_free(arg->read);
	secure_free(arg->path[0]);
	secure_free(arg->pwd);
	cmd_destroy(arg);
	destroy_envlst(arg);
}
