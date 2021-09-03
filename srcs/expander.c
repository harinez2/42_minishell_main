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
	int	i;

	init_env(arg);
	cnt = 0;
	while (arg->cmdlst->param[cnt])
	{
		expander_char(&(arg->cmdlst->param[cnt]), arg);
		cnt ++;
	}
	if (arg->cmdlst->redir_in)
		expander_char(&(arg->cmdlst->redir_in), arg);
	i = 0;
	while (i < arg->cmdlst->redir_out_cnt)
		expander_char(&(arg->cmdlst->redir_out[i++]), arg);
	cmd_print(arg->cmdlst);
}
