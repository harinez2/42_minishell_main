#include "main.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
}
