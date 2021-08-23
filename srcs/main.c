#include "main.h"

static int	fork_and_runcmd(t_arg *arg)
{
	pid_t	pid;
	t_cmd	*c;
	int		status;

	c = arg->cmdlst;
	while (c != NULL)
	{
		if (ft_strncmp("exit", c->cmd, 5) == 0)
		{
			//require memory free
			exit (0);
		}
		else if (run_builtincmd(c->cmd, arg))
			;
		else
		{
			pid = fork();
			if (pid == -1)
				error_exit(ERR_FAILED_TO_FORK, arg);
			else if (pid == 0)
				exec_command(c->cmd, arg);
			waitpid(pid, &status, 0);
			// secure_free(arg->path[0]);
			// if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			// 	return (0);
			// else
			// 	return (-1);
		}
		c = c->next;
	}
	return (0);
}

static int	recog_input(char *read, t_arg *arg)
{
	int		i;
	int		token_type;
	int		starti;
	
	i = 0;
	token_type = 1;
	while (token_type)
	{
		skip_whitespace(read, &i);
		if (read[i] == '\0')
			break ;
		starti = i;
		token_type = get_token(read, &i);
		if (arg->dbg)
		{
			print_token_type(token_type);
			char *s = ft_substr(read, starti, i - starti);
			printf(" %2d-%2d : %s\n", starti, i, s);
			secure_free(s);
		}
		add_tree(arg, token_type, &read[starti], i - starti);
	}
	if (arg->dbg == 1)
		lst_print(arg->cmdlst);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*read;
	int		ret;
	t_arg	arg;

	init_arg(argc, argv, envp, &arg);
	if (argc >= 2 && ft_strncmp("-d", argv[1], 3) == 0)
		arg.dbg = 1;
	while (1)
	{
		read = readline("minishell> ");
		ret = recog_input(read, &arg);
		if (ret == -1)
			break ;
		fork_and_runcmd(&arg);
		lst_destroy(&arg);
		secure_free(read);
	}
	secure_free(read);
	return (0);
}
