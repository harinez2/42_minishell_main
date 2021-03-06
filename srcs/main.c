/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:51 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/19 16:52:05 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	command_execution(t_arg *arg)
{
	int		token_info[MAX_TOKENNUM][3];
	t_cmd	*c;
	int		ret;

	if (lexer(arg, token_info) == -1)
		return (0);
	if (arg->dbg)
		print_token_info(token_info, arg->read);
	if (parser(arg, token_info) == -1)
	{
		ret = arg->last_exit_status;
		cmd_destroy(arg);
		return (ret);
	}
	c = arg->cmdlst;
	while (c)
	{
		expander(arg, c);
		ret = executer(arg, c);
		c = c->next;
	}
	cmd_destroy(arg);
	return (ret);
}

static int	inline_execution(t_arg *arg, char *read)
{
	int		ret;

	arg->read = read;
	ret = command_execution(arg);
	destroy_arg(arg);
	return (ret % 256);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;

	init_arg(argc, argv, envp, &arg);
	set_signal(&arg);
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		return (inline_execution(&arg, argv[2]));
	if (argc >= 2 && ft_strncmp("-d", argv[1], 3) == 0)
		arg.dbg = 1;
	while (1)
	{
		arg.read = readline(SHELL_PROMPT);
		if (arg.read == NULL)
			break ;
		else if (arg.read[0] != '\0')
		{
			add_history(arg.read);
			command_execution(&arg);
		}
		secure_free(arg.read);
	}
	putstr_stderr(GOUP_ONELINE);
	putstr_stderr(SHELL_PROMPT"exit\n");
	destroy_arg(&arg);
	return (0);
}
