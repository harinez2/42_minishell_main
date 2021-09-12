#include "main.h"

static void	command_execution(t_arg *arg)
{
	int		token_info[MAX_TOKENNUM][3];

	if (lexer(arg, token_info) == -1)
		return ;
	if (arg->dbg)
		print_token_info(token_info, arg->read);
	if (parser(arg, token_info) == -1)
	{
		cmd_destroy(arg);
		return ;
	}
	expander(arg);
	executer(arg);
	cmd_destroy(arg);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;

	init_arg(argc, argv, envp, &arg);
	set_signal();
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
	{
		arg.read = argv[2];
		command_execution(&arg);
		return (0);
	}
	if (argc >= 2 && ft_strncmp("-d", argv[1], 3) == 0)
		arg.dbg = 1;
	while (1)
	{
		arg.read = readline(SHELL_PROMPT);
		if (arg.read[0] != '\0')
		{
			add_history(arg.read);
			command_execution(&arg);
		}
		secure_free(arg.read);
	}
	destroy_arg(&arg);
	return (0);
}
