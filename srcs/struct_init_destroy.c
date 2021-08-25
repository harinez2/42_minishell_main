#include "main.h"

static t_cmd	*create_cmdnode(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*c;
	int		i;

	c = malloc(sizeof(t_cmd));
	if (!c)
		error_exit(ERR_FAILED_TO_MALLOC, arg);
	c->param[0] = malloc(sizeof(char) * (len + 1));
	if (!c->param[0])
		error_exit(ERR_FAILED_TO_MALLOC, arg);
	i = 0;
	while (i < len)
	{
		c->param[0][i] = cmdtxt[i];
		i++;
	}
	c->param[0][i] = '\0';
	c->param[1] = NULL;
	c->param_cnt = 0;
	c->nxtcmd_relation = 0;
	c->redir_in = NULL;
	c->redir_out = NULL;
	c->next = NULL;
	c->prev = NULL;
	return (c);
}

int	struct_addlast(t_arg *arg, int addpoint, char *cmdtxt, int len)
{
	t_cmd	*newnode;
	t_cmd	*ctmp;

	if (addpoint == PNT_CMD)
	{
		newnode = create_cmdnode(arg, cmdtxt, len);
		if (arg->cmdlst == NULL)
			arg->cmdlst = newnode;
		else
		{
			ctmp = lst_get_last_cmdnode(arg->cmdlst);
			ctmp->next = newnode;
			newnode->prev = ctmp;
		}
	}
	else if (addpoint == PNT_PARAM)
	{
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
	}
	return (0);
}

void	struct_destroy(t_arg *arg)
{
	t_cmd	*c;
	int		i;

	while (arg->cmdlst != NULL)
	{
		c = arg->cmdlst;
		arg->cmdlst = arg->cmdlst->next;
		i = 0;
		while (i < c->param_cnt + 1)
			secure_free(c->param[i++]);
		secure_free(c->redir_in);
		secure_free(c->redir_out);
		secure_free(c);
	}
}
