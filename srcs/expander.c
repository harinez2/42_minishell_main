#include "main.h"

static void	expander_char(char **text, t_arg *arg)
{
	char	*tmp;

	tmp = *text;
	expander_char_env(text, arg);
	expander_char_quote(text);
}

static void	expander_cmd(t_arg *arg, t_cmd *c)
{
	int	cnt;
	int	i;

	cnt = 0;
	while (c->param[cnt])
	{
		expander_char(&(c->param[cnt]), arg);
		cnt ++;
	}
	if (c->redir_in)
		expander_char(&(c->redir_in), arg);
	i = 0;
	while (i < c->redir_out_cnt)
		expander_char(&(c->redir_out[i++]), arg);
}

void	expander(t_arg *arg)
{
	t_cmd	*c;

	c = arg->cmdlst;
	while (c)
	{
		expander_cmd(arg, c);
		c = c->next;
	}
	if (arg->dbg)
		cmd_print(arg->cmdlst);
}
