#include "main.h"

void	dbg_print_str(t_arg *arg, char *s)
{
	if (!arg->dbg)
		return ;
	write(2, COL_TX_CYAN, ft_strlen(COL_TX_CYAN));
	write(2, s, ft_strlen(s));
	write(2, COL_TX_RESET, ft_strlen(COL_TX_RESET));
}

void	dbg_print_int(t_arg *arg, int i)
{
	char		c;

	if (!arg->dbg)
		return ;
	if (i >= 10)
		dbg_print_int(arg, i / 10);
	c = i % 10 + '0';
	write(2, COL_TX_CYAN, ft_strlen(COL_TX_CYAN));
	write(2, &c, 1);
	write(2, COL_TX_RESET, ft_strlen(COL_TX_RESET));
}

void	dbg_print_strint(t_arg *arg, char *s, int i)
{
	dbg_print_str(arg, s);
	dbg_print_str(arg, " ");
	dbg_print_int(arg, i);
	dbg_print_str(arg, "\n");
}

void	copy_array(int *to, int *from, int len, int offset_to)
{
	int		i;

	i = 0;
	while (i < len)
	{
		to[offset_to + i] = from[i];
		i++;
	}
}

void	secure_free(void *p)
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}

void	init_arg(int argc, char **argv, char **envp, t_arg *arg)
{
	int		i;

	arg->argc = argc;
	arg->argv = argv;
	arg->envp = envp;
	arg->cmdlst = NULL;
	i = -1;
	arg->path_cnt = 0;
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			arg->path[arg->path_cnt++] = ft_strdup(&envp[i][5]);
	if (arg->path_cnt != 1)
		error_exit(ERR_ENV_INVALID, NULL);
	i = 0;
	while (arg->path[0][i] != '\0')
	{
		if (arg->path[0][i] == ':')
		{
			arg->path[0][i++] = '\0';
			arg->path[arg->path_cnt++] = &arg->path[0][i];
		}
		i++;
	}
	arg->path[arg->path_cnt] = NULL;
	arg->dbg = 0;
}
