#include "main.h"

// static void	dbgprint_tokeninfo(int token_type, char *read, int starti, int i)
// {
// 	char	*s;

// 	print_token_type(token_type);
// 	s = ft_substr(read, starti, i - starti);
// 	printf(" %2d-%2d : %s\n", starti, i, s);
// 	secure_free(s);
// }

static int	recog_input(char *read, t_arg *arg)
{
	int		i;
	int		token_type;
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
		token_type = get_token(read, &i);
		
		token_info[tki_i][0] = token_type;
		token_info[tki_i++][1] = starti;

		// if (arg->dbg)
		// 	dbgprint_tokeninfo(token_type, read, starti, i);
		// add_tree(arg, token_type, &read[starti], i - starti);
	}
	token_info[tki_i][0] = TKN_EOF;
	token_info[tki_i++][1] = i;

	if (arg->dbg)
	{
		printf("<<lexer results>>\n");
		printf(" i  token-type     starti  content\n");
		for(int i = 0; i < tki_i; i++)
		{
			printf("%2d  ", i);
			print_token_type(token_info[i][0]);
			printf("    %3d     ", token_info[i][1]);
			ft_putstr(read + token_info[i][1], token_info[i + 1][1] - token_info[i][1]);
			printf("\n");
		}
		printf("\n");
	}
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
