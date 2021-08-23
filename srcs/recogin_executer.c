#include "main.h"

int	fork_and_runcmd(t_arg *arg)
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
