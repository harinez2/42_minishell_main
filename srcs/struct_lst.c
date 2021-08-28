#include "main.h"

t_cmd	*cmd_get_last_node(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
