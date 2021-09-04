#include "main.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, &BACK_CURSOR, ft_strlen(BACK_CURSOR));
	write(1, &CLEAR_FROM_CURSOR, ft_strlen(CLEAR_FROM_CURSOR));
	write(1, &"\n"SHELL_PROMPT, ft_strlen("\n"SHELL_PROMPT));
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
}
