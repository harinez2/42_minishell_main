/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:40:38 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:40:38 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_env_with_envname_only(t_arg *arg, char *envname)
{
	t_env	*e;

	e = get_node_from_envlst(arg->shellenvlst, envname);
	if (e)
	{
		if (arg->dbg)
			printf(" found in shellenv :%s=%s\n", e->env, e->value);
		push_back_envlst(
			&arg->envlst, ft_strdup(envname), ft_strdup(e->value), arg);
		delete_env_from_envlst(&arg->shellenvlst, envname);
		return ;
	}
	e = get_node_from_envlst(arg->envlst, envname);
	if (!e)
		push_back_envlst(&arg->envlst, ft_strdup(envname), NULL, arg);
}

static void	set_env_with_envname_and_value(
	t_arg *arg, char *envname, char *envvalue)
{
	delete_env_from_envlst(&arg->shellenvlst, envname);
	push_back_envlst(&arg->envlst, ft_strdup(envname),
		envvalue, arg);
}

static int	add_oneparam(t_arg *arg, t_cmd *cmd, int i)
{
	int		eqpos;
	int		len;
	int		plus;
	char	*envname;

	if (!is_valid_env_definition(cmd->param[i])
		&& !is_shellver_char(cmd->param[i], 0, ft_strlen(cmd->param[i])))
		return (print_custom_error(
				ERR_NOT_VALID_IDENTIFIER, cmd->param[0], cmd->param[i], arg));
	eqpos = ft_strchr(cmd->param[i], '=');
	len = ft_strlen(cmd->param[i]);
	plus = 0;
	if (eqpos != len && cmd->param[i][eqpos - 1] == '+')
		plus = 1;
	envname = ft_substr(cmd->param[i], 0, eqpos - plus);
	if (plus && concat_envvalue(cmd->param[i], eqpos, len, arg) == 1)
		;
	else if (eqpos == len)
		set_env_with_envname_only(arg, envname);
	else
		set_env_with_envname_and_value(
			arg, envname, ft_substr(cmd->param[i], eqpos + 1, len));
	secure_free(envname);
	return (0);
}

int	builtincmd_export_witharg(t_arg *arg, t_cmd *cmd)
{
	int		i;
	int		ret;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd export(witharg) ===\n");
	ret = 0;
	i = 1;
	while (cmd->param[i])
	{
		ret |= add_oneparam(arg, cmd, i);
		i++;
	}
	return (ret);
}

int	builtincmd_export_noarg(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd export(noarg) ===\n");
	print_env_export(arg);
	return (0);
}
