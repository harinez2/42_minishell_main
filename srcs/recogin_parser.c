#include "main.h"

// <redirection> ::=
// 	"<" string
// 	|	">" string
// 	|	"<<" string
// 	|	">>" string
int	bnf_redirection(t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (arg->dbg)
		printf("%2d <redirection>\n", *i);
	if (token_info[*i][0] == TKN_REDIR_LEFT
		|| token_info[*i][0] == TKN_REDIR_RIGHT
		|| token_info[*i][0] == TKN_HEREDOC
		|| token_info[*i][0] == TKN_REDIR_APPEND)
	{
		(*i)++;
		if (token_info[*i][0] == TKN_STRING)
		{
			if (arg->dbg)
				printf("   =string: redir filename=\n");
			if (token_info[*i - 1][0] == TKN_REDIR_LEFT)
			{
				if (arg->dbg)
					printf("   =<=\n");
				if (leftflg)
					cmd_create_node_with_redir(arg, 0,
						arg->read + token_info[*i][1],
						token_info[*i][2] - token_info[*i][1]);
				else
					cmd_add_redir_filename(arg, 0,
						arg->read + token_info[*i][1],
						token_info[*i][2] - token_info[*i][1]);
			}
			else if (token_info[*i - 1][0] == TKN_REDIR_RIGHT)
			{
				if (arg->dbg)
					printf("   =>=\n");
				if (leftflg)
					cmd_create_node_with_redir(arg, 1,
						arg->read + token_info[*i][1],
						token_info[*i][2] - token_info[*i][1]);
				else
					cmd_add_redir_filename(arg, 1,
						arg->read + token_info[*i][1],
						token_info[*i][2] - token_info[*i][1]);
			}
			else if (token_info[*i - 1][0] == TKN_HEREDOC)
			{
				if (arg->dbg)
					printf("   =<<=\n");
			}
			else if (token_info[*i - 1][0] == TKN_REDIR_APPEND)
			{
				if (arg->dbg)
					printf("   =>>=\n");
			}
			else
				return (-1);
			(*i)++;
		}
		else
			return (-1);
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
		cmd_add_setflg(arg, CONN_AMP);
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

// <param_redir> ::=
// 	string
// 	|	<redirection>
int	bnf_param_redir(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <param_redir>\n", *i);
	if (token_info[*i][0] == TKN_STRING)
	{
		if (arg->dbg)
			printf("   =string: param=\n");
		cmd_add_param(arg, arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
		(*i)++;
	}
	else if (bnf_redirection(arg, token_info, i, 0) == 0)
		;
	else
		return (-1);
	return (0);
}

// <command_elements> ::=
// 	<param_redir> 
// 	|	<param_redir>  <command_elements>
int	bnf_command_elements(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <command_elements>\n", *i);
	if (bnf_param_redir(arg, token_info, i) == 0)
	{
		bnf_command_elements(arg, token_info, i);
	}
	else
		return (-1);
	return (0);
}

// <simple_command> ::=
// 	string
int	bnf_simple_command(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <simple_command>\n", *i);
	if (token_info[*i][0] == TKN_STRING)
	{
		if (arg->dbg)
			printf("   =string: cmd=\n");
		cmd_create_node_with_param(arg, arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
		(*i)++;
	}
	else
		return (-1);
	return (0);
}

// <compoud_command> ::=
// 	<redirection> <simple_command>
// 	|	<redirection> <simple_command> <command_elements>
// 	|	<simple_command>
// 	|	<simple_command> <command_elements>
int	bnf_compoud_command(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <compoud_command>\n", *i);
	if (bnf_redirection(arg, token_info, i, 1) == 0)
	{
		if (bnf_simple_command(arg, token_info, i) == 0)
		{
			bnf_command_elements(arg, token_info, i);
		}
		else
			return (-1);
	}
	else if (bnf_simple_command(arg, token_info, i) == 0)
	{
		bnf_command_elements(arg, token_info, i);
	}
	else
		return (-1);
	return (0);
}

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
			cmd_add_setflg(arg, CONN_PIPE);
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
		printf("##### parse failed! #####\n\n");
		// error_exit(-1, arg);
	}
	return (0);
}
