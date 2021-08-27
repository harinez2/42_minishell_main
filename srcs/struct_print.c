#include "main.h"

static void	struct_print_int(char *basetxt, int i)
{
	printf("%s", basetxt);
	if (i == CONN_PIPE)
		printf("CONN_PIPE\n");
	else if (i == CONN_REDIR_OUT)
		printf("CONN_REDIR_OUT\n");
	else
		printf("%d\n", i);
}

static void	struct_print_char(char *basetxt, char *param)
{
	printf("%s", basetxt);
	if (param == NULL)
		printf("<NULL>\n");
	else
		printf("%s\n", param);
}

void	struct_print(t_cmd *c)
{
	int			i;
	int			j;

	printf("<<< command chain >>>\n");
	i = 0;
	while (c != NULL)
	{
		printf("[%d]\n", i);
		printf("  param[0] : %s\n", c->param[0]);
		j = 1;
		while (j <= c->param_cnt)
		{
			printf("  param[%d] : ", j);
			struct_print_char("", c->param[j++]);
		}
		struct_print_int("  nxtrel   : ", c->nxtcmd_relation);
		struct_print_int("  pipe[0]  : ", c->pipe[0]);
		struct_print_int("  pipe[1]  : ", c->pipe[1]);
		struct_print_char("  redir_in : ", c->redir_in);
		struct_print_char("  redir_out: ", c->redir_out);
		c = c->next;
		i++;
	}
	printf("\n");
}
