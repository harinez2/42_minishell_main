#include "main.h"

static void	add_pipeflg(t_arg *arg)
{
	t_cmd	*c;

	c = lst_get_last_cmdnode(arg->cmdlst);
	c->nxtcmd_relation = CONN_PIPE;
}

void	add_tree(t_arg *arg, int type, char *cmdtxt, int len)
{
	if (type == TKN_DBLQUOTE)
		struct_addlast(arg, PNT_PARAM, cmdtxt, len);
	else if (type == TKN_SGLQUOTE)
		;
	else if (type == TKN_COLON)
		;
	else if (type == TKN_AMP)
		;
	else if (type == TKN_SINGLE_OR)
		add_pipeflg(arg);
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
		struct_addlast(arg, PNT_CMD, cmdtxt, len);
	}
}
