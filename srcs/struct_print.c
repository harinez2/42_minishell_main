#include "main.h"

static void	cmd_print_int(char *basetxt, int i)
{
	printf("%s", basetxt);
	if (i == CONN_PIPE)
		printf("CONN_PIPE\n");
	else if (i == CONN_REDIR_OUT)
		printf("CONN_REDIR_OUT\n");
	else
		printf("%d\n", i);
}

static void	cmd_print_onecmd(int i, t_cmd *c)
{
	int			j;

	printf("[%d]\n", i);
	j = 0;
	while (j <= c->param_cnt)
	{
		printf("  param[%d]    : %s\n", j, c->param[j]);
		j++;
	}
	cmd_print_int("  nxtrel      : ", c->nxtcmd_relation);
	cmd_print_int("  pipe[0]     : ", c->pipe[0]);
	cmd_print_int("  pipe[1]     : ", c->pipe[1]);
	cmd_print_int("  heredoc_flg : ", c->heredoc_flg);
	printf("  redir_in    : %s\n", c->redir_in);
	j = -1;
	while (++j < c->redir_out_cnt)
		printf("  append_flg[%d]: %d\n", j, c->append_flg[j]);
	j = -1;
	while (++j < c->redir_out_cnt)
		printf("  redir_out[%d] : %s\n", j, c->redir_out[j]);
}

void	cmd_print(t_cmd *c)
{
	int			i;

	printf(COL_TX_CYAN"<<< command chain >>>\n"COL_TX_RESET);
	i = 0;
	while (c != NULL)
	{
		cmd_print_onecmd(i, c);
		c = c->next;
		i++;
	}
	printf("\n");
}
