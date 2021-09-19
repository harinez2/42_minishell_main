/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:07 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 17:40:56 by yonishi          ###   ########.fr       */
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

// Ctrl+C : SIGINT
// Ctrl+\ : SIGQUIT
// Ctrl+D : send EOF (not signal, supported in main() func)
void	set_signal(t_arg *arg)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
}

void	ignore_all_signal(t_arg *arg)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
}

void	reset_signal(t_arg *arg)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_perror_exit(errno, NULL, NULL, arg);
}
