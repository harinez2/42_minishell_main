#include "main.h"

int	struct_add_pipeflg(t_arg *arg)
{
	t_cmd	*c;

	c = lst_get_last_cmdnode(arg->cmdlst);
	if (c == NULL)
		return (-1);//parsing error
	c->nxtcmd_relation = CONN_PIPE;
	return (0);
}

int	struct_add_param(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*newnode;
	t_cmd	*ctmp;

	newnode = malloc(sizeof(char) * (len + 1));
	if (!newnode)
		error_exit(ERR_FAILED_TO_MALLOC, arg);
	ctmp = lst_get_last_cmdnode(arg->cmdlst);
	if (ctmp == NULL)
		return (-1);//parsing error
	else
	{
		ctmp->param[ctmp->param_cnt++] = ft_substr(cmdtxt, 0, len);
		ctmp->param[ctmp->param_cnt] = NULL;
	}
	return (0);
}
