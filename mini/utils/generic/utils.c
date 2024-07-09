#include "../utils.h"

void memoryerror(t_mini *mini)
{
	mini->exit_status = 1;
	perror("Malloc/Calloc error\n");
}