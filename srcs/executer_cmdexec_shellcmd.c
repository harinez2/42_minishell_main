/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmdexec_shellcmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:05 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:41:05 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	exec_shellcmd_execve(t_cmd *cmd, t_arg *arg, char **env)
{
	int			ret;
	int			stat_ret;
	struct stat	sb;

	ret = -1;
	stat_ret = stat(cmd->param[0], &sb);
	ret = errno;
	if (arg->dbg)
	{
		printf("  searching file...%s (stat() ret:%d, S_ISREG:%d, errno:%d)",
			cmd->param[0], stat_ret, S_ISREG(sb.st_mode), ret);
		if (stat_ret == -1)
			printf("...not found.\n");
		else
			printf("...found. try execution.\n");
	}
	if (stat_ret == 0 && S_ISDIR(sb.st_mode))
		ret = EISDIR;
	else if (stat_ret == 0 && S_ISREG(sb.st_mode))
	{
		dbg_print_cmdstart(arg, cmd->param[0]);
		execve(cmd->param[0], cmd->param, env);
		ret = errno;
	}
	return (ret);
}

static int	exec_shellcmd_relativepath(t_cmd *cmd, t_arg *arg, char **env)
{
	int		ret;
	char	*param_zero;

	param_zero = cmd->param[0];
	cmd->param[0] = ft_strjoin(arg->pwd, param_zero + 1);
	ret = exec_shellcmd_execve(cmd, arg, env);
	secure_free(cmd->param[0]);
	cmd->param[0] = param_zero;
	return (ret);
}

static int	exec_shellcmd_with_envpath(t_cmd *cmd, t_arg *arg, char **env)
{
	int		ret;
	char	*param_zero;
	int		i;

	ret = -1;
	i = 0;
	param_zero = cmd->param[0];
	while (ret != 0 && i < arg->path_cnt)
	{
		cmd->param[0] = ft_strjoin3(arg->path[i], "/", param_zero);
		ret = exec_shellcmd_execve(cmd, arg, env);
		secure_free(cmd->param[0]);
		i++;
	}
	cmd->param[0] = param_zero;
	return (ret);
}

static void	display_errmsg(t_arg *arg, t_cmd *cmd, int ret, int envpathflg)
{
	if (arg->dbg)
		printf("  command execution failed: %d\n", ret);
	if (envpathflg && (ret == ENOENT || ret == -1))
		print_custom_error_exit(ERR_FAILED_TO_EXEC, cmd->param[0], NULL, arg);
	else
		print_perror_exit(ret, cmd->param[0], NULL, arg);
}

int	exec_shellcmd(t_cmd *cmd, t_arg *arg)
{
	int		ret;
	char	**env;

	env = generate_environ(arg);
	if (cmd->param[0][0] == '/')
		ret = exec_shellcmd_execve(cmd, arg, env);
	else if (ft_strncmp(cmd->param[0], "./", 2) == 0)
		ret = exec_shellcmd_relativepath(cmd, arg, env);
	else
	{
		ret = exec_shellcmd_with_envpath(cmd, arg, env);
		destroy_environ(env);
		display_errmsg(arg, cmd, ret, 1);
		return (ret);
	}
	destroy_environ(env);
	display_errmsg(arg, cmd, ret, 0);
	return (ret);
}
