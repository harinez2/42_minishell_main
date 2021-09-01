#include "main.h"

static int	read_parameter(t_cmd *cmd, int *i)
{
	int		j;
	int		nflg;
	int		nflg_reading;

	nflg = 0;
	while (cmd->param[*i])
	{
		if (cmd->param[*i][0] != '-')
			break ;
		j = 1;
		nflg_reading = 0;
		while (cmd->param[*i][j])
		{
			if (cmd->param[*i][j] == 'n')
				nflg_reading = 1;
			else if (ft_searchinstr("eE", cmd->param[*i][j]))
				;
			else
				return (nflg);
			j++;
		}
		nflg |= nflg_reading;
		(*i)++;
	}
	return (nflg);
}

void	builtincmd_echo(t_arg *arg, t_cmd *cmd)
{
	int		i;
	int		nflg;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd echo ===\n");
	i = 1;
	nflg = read_parameter(cmd, &i);
	while (cmd->param[i])
	{
		printf("%s", cmd->param[i]);
		i++;
		if (cmd->param[i] == NULL)
			break ;
		printf(" ");
	}
	if (!nflg)
		printf("\n");
}
