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
		error_exit(ERR_FAILED_TO_MALLOC, NULL, arg);
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

int	cmd_add_flg(t_arg *arg, t_token_type t, int flg)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	if (t == TKN_SINGLE_OR || t == TKN_AMP)
		c->nxtcmd_relation = flg;
	else if (t == TKN_HEREDOC)
		c->heredoc_flg = 1;
	else if (t == TKN_REDIR_APPEND)
		c->append_flg = 1;
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
