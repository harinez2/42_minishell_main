#include "main.h"

void	dbg_print_str(t_arg *arg, char *s)
{
	if (!arg->dbg)
		return ;
	write(2, COL_TX_CYAN, ft_strlen(COL_TX_CYAN));
	write(2, s, ft_strlen(s));
	write(2, COL_TX_RESET, ft_strlen(COL_TX_RESET));
}

void	dbg_print_int(t_arg *arg, int i)
{
	char		c;

	if (!arg->dbg)
		return ;
	if (i >= 10)
		dbg_print_int(arg, i / 10);
	c = i % 10 + '0';
	write(2, COL_TX_CYAN, ft_strlen(COL_TX_CYAN));
	write(2, &c, 1);
	write(2, COL_TX_RESET, ft_strlen(COL_TX_RESET));
}

void	dbg_print_strint(t_arg *arg, char *s, int i)
{
	dbg_print_str(arg, s);
	dbg_print_str(arg, " ");
	dbg_print_int(arg, i);
	dbg_print_str(arg, "\n");
}
