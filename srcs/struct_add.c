#include "main.h"

// in:0, out:1
int	cmd_add_redir_filename(t_arg *arg, int inout, char *read, int len)
{
	t_cmd	*c;
	char	*filename;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
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

int	cmd_add_flg_heredoc(t_arg *arg, int flg)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	c->heredoc_flg = flg;
	return (0);
}

int	cmd_add_flg_nxtcmdrel(t_arg *arg, int flg)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	c->nxtcmd_relation = flg;
	return (0);
}

int	cmd_add_param(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	c->param[c->param_cnt++] = ft_substr(cmdtxt, 0, len);
	c->param[c->param_cnt] = NULL;
	return (0);
}
