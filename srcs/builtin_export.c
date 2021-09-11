#include "main.h"

static int	add_oneparam(t_arg *arg, t_cmd *cmd, int i)
{
	int		eqpos;
	int		paramlen;
	char	*envname;
	t_env	*e;

	eqpos = ft_strchr(cmd->param[i], '=');
	if (eqpos == 0)
		return (print_custom_error(
				ERR_NOT_VALID_IDENTIFIER, cmd->param[0], cmd->param[i], arg));
	paramlen = ft_strlen(cmd->param[i]);
	envname = ft_substr(cmd->param[i], 0, eqpos);
	if (eqpos == paramlen)
	{
		e = get_node_from_envlst(arg->shellenvlst, envname);
		if (e != NULL)
			push_back_envlst(&arg->envlst, envname, ft_strdup(e->value), arg);
		else
			push_back_envlst(&arg->envlst, envname, NULL, arg);
	}
	else
		push_back_envlst(&arg->envlst, envname,
			ft_substr(cmd->param[i], eqpos + 1, paramlen), arg);
	delete_env_from_envlst(&arg->shellenvlst, envname);
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
