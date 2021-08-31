#include "main.h"

void	expander_char(char **text, t_arg *arg)
{
	char	*tmp;

	tmp = *text;
	expander_char_env(text, arg);
	expander_char_quote(text);
}

void	expander(t_arg *arg)
{
	int	cnt;

	init_env(arg);
	cnt = 0;
	while (arg->cmdlst->param[cnt])
	{
		expander_char(&(arg->cmdlst->param[cnt]), arg);
		cnt ++;
	}
	if (arg->cmdlst->redir_in)
		expander_char(&(arg->cmdlst->redir_in), arg);
	if (arg->cmdlst->redir_out)
		expander_char(&(arg->cmdlst->redir_out), arg);
	cmd_print(arg->cmdlst);
}
