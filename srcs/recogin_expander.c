#include "main.h"

void	expander_char(t_arg *arg, int option)
{
	(void)arg;
	(void)option;
}

void	expander_multiple_char(t_arg *arg)
{
	int	cnt;
	
	cnt = 0;
	while (arg->cmdlst->param[cnt])
	{
		expander_char(arg, cnt);
	}
}

void	expander(t_arg *arg)
{
	expander_multiple_char(arg);
}
