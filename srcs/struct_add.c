#include "main.h"

// in:0, out:1
int	struct_add_redir_filename(t_arg *arg, int inout, char *read, int len)
{
	t_cmd	*c;
	char	*filename;

	c = lst_get_last_cmdnode(arg->cmdlst);
	if (c == NULL)
		return (-1);//parsing error
	filename = malloc(sizeof(char) * (len + 1));
	if (!filename)
		error_exit(-1, arg);
	ft_strlcpy(filename, read, len + 1);
	if (inout == 0)
	{
		if (c->redir_in != NULL)
			free(c->redir_in);
		c->redir_in = filename;
	}
	else
	{
		if (c->redir_out != NULL)
			free(c->redir_out);
		c->redir_out = filename;
	}
	return (0);
}

int	struct_add_setflg(t_arg *arg, int flg)
{
	t_cmd	*c;

	c = lst_get_last_cmdnode(arg->cmdlst);
	if (c == NULL)
		return (-1);//parsing error
	c->nxtcmd_relation = flg;
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
