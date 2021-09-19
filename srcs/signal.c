/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:07 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 19:33:30 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler_printreturn(int signum)
{
	if (signum == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else
		write(1, "\n", 1);
}

// Ctrl+C : SIGINT
// Ctrl+\ : SIGQUIT
// Ctrl+D : send EOF (not signal, supported in main() func)
void	set_signal(t_arg *arg)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
}

void	ignore_all_signal(t_arg *arg)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGINT, sig_handler_printreturn) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, sig_handler_printreturn) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
}

void	reset_signal(t_arg *arg)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
}
