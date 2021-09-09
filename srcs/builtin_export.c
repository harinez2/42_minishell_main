#include "main.h"

static void	add_oneparam(t_arg *arg, t_cmd *cmd, int i)
{
	int		eqpos;
	int		paramlen;
	char	*envname;
	t_env	*e;

	eqpos = ft_strchr(cmd->param[i], '=');
	paramlen = ft_strlen(cmd->param[i]);
	envname = ft_substr(cmd->param[i], 0, eqpos);
	e = get_node_from_envlst(arg->shellenvlst, envname);
	if (e != NULL)
	{
		if (eqpos == paramlen)
			push_back_envlst(&arg->envlst, envname, ft_strdup(e->value), arg);
		else
			push_back_envlst(&arg->envlst, envname,
				ft_substr(cmd->param[i], eqpos + 1, paramlen), arg);
		delete_env_from_envlst(&arg->shellenvlst, envname);
	}
	else if (eqpos == paramlen)
		push_back_envlst(&arg->envlst, envname, NULL, arg);
	else
		push_back_envlst(&arg->envlst, envname,
			ft_substr(cmd->param[i], eqpos + 1, paramlen), arg);
}

void	builtincmd_export_witharg(t_arg *arg, t_cmd *cmd)
{
	int		i;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd export(witharg) ===\n");
	i = 1;
	while (cmd->param[i])
	{
		add_oneparam(arg, cmd, i);
		i++;
	}
}

int	builtincmd_export_noarg(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd export(noarg) ===\n");
	print_env_export(arg);
	return (0);
}
