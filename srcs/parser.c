#include "main.h"

// <piped_commands> ::=
// 	<compoud_command>
// 	|	<compoud_command> '|' <piped_commands>
int	bnf_piped_commands(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <piped_commands>\n", *i);
	if (bnf_compoud_command(arg, token_info, i) == 0)
	{
		if (token_info[*i][0] == TKN_SINGLE_OR)
		{
			if (arg->dbg)
				printf("   =|=\n");
			cmd_add_flg(arg, TKN_SINGLE_OR, CONN_PIPE);
			(*i)++;
			if (bnf_piped_commands(arg, token_info, i) == 0)
				;
			else
				return (-1);
		}
	}
	else
		return (-1);
	return (0);
}

// <separation_op> ::=
// 	'&'
// 	|	';'
int	bnf_separation_op(t_arg *arg, int token_info[][3], int *i)
{
	(void)read;
	if (arg->dbg)
		printf("%2d <separation_op>\n", *i);
	if (token_info[*i][0] == TKN_AMP)
	{
		if (arg->dbg)
			printf("   =&=\n");
		cmd_add_flg(arg, TKN_AMP, CONN_AMP);
		(*i)++;
	}
	else if (token_info[*i][0] == TKN_SEMICOLON)
	{
		if (arg->dbg)
			printf("   =;=\n");
		(*i)++;
	}
	else
		return (-1);
	return (0);
}

// <command_line> ::
// 	<piped_commands>
// 	|	<piped_commands> <separation_op>
// 	| 	<piped_commands> <separation_op> <command_line>
int	bnf_command_line(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <command_line>\n", *i);
	if (bnf_piped_commands(arg, token_info, i) == 0)
	{
		if (bnf_separation_op(arg, token_info, i) == 0)
		{
			bnf_command_line(arg, token_info, i);
		}
	}
	else
		return (-1);
	return (0);
}

int	parser(t_arg *arg, int token_info[][3])
{
	int		i;

	if (arg->dbg)
		printf(COL_TX_CYAN"<<< parser results >>>\n"COL_TX_RESET);
	i = 0;
	if (bnf_command_line(arg, token_info, &i) == 0
		&& token_info[i][0] == TKN_EOF)
	{
		if (arg->dbg)
			printf("parse ok!\n\n");
	}
	else
	{
		if (arg->dbg)
			printf("##### parse failed! #####\n\n");
		error_exit(ERR_SYNTAX_ERROR, NULL, arg);
	}
	return (0);
}
