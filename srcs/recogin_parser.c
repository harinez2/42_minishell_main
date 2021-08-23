#include "main.h"

void	add_tree(t_arg *arg, int type, char *cmdtxt, int len)
{
	if (type == TKN_DBLQUOTE)
		lst_addlast(arg, PNT_PARAM, cmdtxt, len);
	else if (type == TKN_SGLQUOTE)
		;
	else if (type == TKN_COLON)
		;
	else if (type == TKN_AMP)
		;
	else if (type == TKN_SINGLE_OR)
		;
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
		lst_addlast(arg, PNT_CMD, cmdtxt, len);
	}
}
