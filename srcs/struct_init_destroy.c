#include "main.h"

static t_cmd	*cmd_create_empty_node(t_arg *arg)
{
	t_cmd	*c;

	c = malloc(sizeof(t_cmd));
	if (!c)
		error_exit(ERR_FAILED_TO_MALLOC, "", arg);
	c->param[0] = NULL;
	c->param_cnt = 0;
	c->nxtcmd_relation = 0;
	c->pipe[0] = -1;
	c->pipe[1] = -1;
	c->heredoc_flg = 0;
	c->redir_in = NULL;
	c->append_flg = 0;
	c->redir_out = NULL;
	c->next = NULL;
	c->prev = NULL;
	return (c);
}

static int	cmd_add_last(t_arg *arg, t_cmd *c_add)
{
	t_cmd	*c;

	if (arg->cmdlst == NULL)
		arg->cmdlst = c_add;
	else
	{
		c = cmd_get_last_node(arg->cmdlst);
		c->next = c_add;
		c_add->prev = c;
	}
	return (0);
}

t_cmd	*cmd_create_node_with_param(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c != NULL && c->param[0] == NULL)
	{
		cmd_add_param(arg, cmdtxt, len);
		return (c);
	}
	c = cmd_create_empty_node(arg);
	cmd_add_last(arg, c);
	cmd_add_param(arg, cmdtxt, len);
	return (c);
}

// in:0, out:1
t_cmd	*cmd_create_node_with_redir(
	t_arg *arg, int inout, char *cmdtxt, int len)
{
	t_cmd	*c;

	c = cmd_create_empty_node(arg);
	cmd_add_last(arg, c);
	cmd_add_redir_filename(arg, inout, cmdtxt, len);
	return (c);
}

void	cmd_destroy(t_arg *arg)
{
	t_cmd	*c;
	int		i;

	while (arg->cmdlst != NULL)
	{
		c = arg->cmdlst;
		arg->cmdlst = arg->cmdlst->next;
		i = 0;
		while (i < c->param_cnt)
			secure_free(c->param[i++]);
		if (c->heredoc_flg)
			unlink(c->redir_in);
		secure_free(c->redir_in);
		secure_free(c->redir_out);
		secure_free(c);
	}
}
