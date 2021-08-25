#include "main.h"

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
