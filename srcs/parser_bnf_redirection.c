#include "main.h"

static void	bnf_redirection_left(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
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

static void	bnf_redirection_right(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
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

static void	bnf_redirection_heredoc(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	char	*filename;

	if (arg->dbg)
		printf("   =<<=\n");
	filename = heredoc_read(arg, arg->read + token_info[*i][1]);
	if (leftflg)
		cmd_create_node_with_redir(arg, 0, filename,
			HEREDOC_FILENAME_LEN);
	else
		cmd_add_redir_filename(arg, 0, filename,
			HEREDOC_FILENAME_LEN);
	cmd_add_flg_heredoc(arg, 1);
	secure_free(filename);
}

static void	bnf_redirection_append(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (arg->dbg)
		printf("   =>>=\n");
	(void)token_info;
	(void)i;
	(void)leftflg;
}

void	bnf_redirection_op(t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (token_info[*i - 1][0] == TKN_REDIR_LEFT)
		bnf_redirection_left(arg, token_info, i, leftflg);
	else if (token_info[*i - 1][0] == TKN_REDIR_RIGHT)
		bnf_redirection_right(arg, token_info, i, leftflg);
	else if (token_info[*i - 1][0] == TKN_HEREDOC)
		bnf_redirection_heredoc(arg, token_info, i, leftflg);
	else if (token_info[*i - 1][0] == TKN_REDIR_APPEND)
		bnf_redirection_append(arg, token_info, i, leftflg);
}
