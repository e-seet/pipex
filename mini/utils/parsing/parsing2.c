#include "../utils.h"

// 1. check it is semicolon, then move to next node and skip this if statement
// otherwise delete the node and move on
// 2. Look for the next command line
// if null delete
struct s_AST_Node	*breakjob1(t_linkedlist *node)
{
	struct s_AST_Node	*command_node;
	struct s_AST_Node	*job_node;
	struct s_AST_Node	*rootnode;

	command_node = breakcommand(node);
	if (command_node == NULL)
		return (NULL);
	if (!term(PIPE, NULL, &node))
	{
		nodedelete(command_node);
		return (NULL);
	}
	job_node = breakjob(node);
	if (job_node == NULL)
	{
		nodedelete(job_node);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_PIPE);
	nodesetdata(rootnode, NULL);
	attachbinarybranch(rootnode, command_node, job_node);
	return (rootnode);
}

struct s_AST_Node	*breakjob2(t_linkedlist *node)
{
	return (breakcommand(node));
}
