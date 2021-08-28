#include "main.h"

static void	command_execution(t_arg *arg, char *read)
{
	int		token_info[1000][3];

	lexer(arg, read, token_info);
	if (arg->dbg)
		print_token_info(token_info, read);
	parser(token_info, read, arg);
	if (arg->dbg)
		cmd_print(arg->cmdlst);
	expander(arg);
	executer(arg);
	cmd_destroy(arg);
}

int	main(int argc, char **argv, char **envp)
{
	char	*read;
	t_arg	arg;

	init_arg(argc, argv, envp, &arg);
	if (argc >= 2 && ft_strncmp("-d", argv[1], 3) == 0)
		arg.dbg = 1;
	while (1)
	{
		read = readline("minishell> ");
		command_execution(&arg, read);
		secure_free(read);
	}
	return (0);
}
