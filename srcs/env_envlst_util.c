#include "main.h"

t_env	*get_node_from_envlst(t_env	*envlst, char *envname)
{
	t_env		*e;

	e = envlst;
	while (e != NULL)
	{
		if (ft_strncmp(e->env, envname, ft_strlen(envname) + 1) == 0)
			return (e);
		e = e->next;
	}
	return (NULL);
}

int	count_envlst(t_arg *arg)
{
	t_env	*e;
	int		ret;

	ret = 0;
	e = arg->envlst;
	while (e)
	{
		ret++;
		e = e->next;
	}
	return (ret);
}
