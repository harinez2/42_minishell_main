#include "main.h"

void	add_tree(t_arg *arg, int type, char *cmdtxt, int len)
{
	if (type == TKN_DBLQUOTE)
		struct_add_param(arg, cmdtxt, len);
	else if (type == TKN_SGLQUOTE)
		;
	else if (type == TKN_COLON)
		;
	else if (type == TKN_AMP)
		;
	else if (type == TKN_SINGLE_OR)
		struct_add_pipeflg(arg);
	else if (type == TKN_REDIR_LEFT)
		;
	else if (type == TKN_REDIR_RIGHT)
		;
	else if (type == TKN_HEREDOC)
		;
	else if (type == TKN_DBLANDOR)
		;
	else if (type == TKN_CHAR)
	{
		struct_add_node(arg, cmdtxt, len);
	}
}
