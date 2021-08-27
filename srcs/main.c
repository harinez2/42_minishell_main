#include "main.h"

static int	recog_input(char *read, t_arg *arg)
{
	int		i;
	int		starti;
	int		token_info[1000][2];
	int		tki_i;

	i = 0;
	tki_i = 0;
	while (1)
	{
		skip_whitespace(read, &i);
		if (read[i] == '\0')
			break ;
		starti = i;
		token_info[tki_i][0] = get_token(read, &i);
		token_info[tki_i++][1] = starti;
	}
	token_info[tki_i][0] = TKN_EOF;
	token_info[tki_i++][1] = i;
	if (arg->dbg)
		print_token_info(token_info, read);
	parser(token_info, read, arg);
	if (arg->dbg == 1)
		struct_print(arg->cmdlst);
	expander(arg);
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
		executer(&arg);
		struct_destroy(&arg);
		secure_free(read);
	}
	secure_free(read);
	return (0);
}
