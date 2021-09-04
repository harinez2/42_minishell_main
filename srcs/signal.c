#include "main.h"

void	sigint_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, &BACK_CURSOR, ft_strlen(BACK_CURSOR));
	write(1, &CLEAR_FROM_CURSOR, ft_strlen(CLEAR_FROM_CURSOR));
	write(1, &"\n", 1);
	rl_redisplay();
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
}
