#include "../utils.h"

// first layer

// 1. check it is semicolon, then move to next node and skip this if statement
// otherwise delete the node and move on
// 2.Look for the next command line
// if null delete
struct s_AST_Node	*breakcommandline1(t_linkedlist *node)
{
	struct s_AST_Node	*job_node;
	struct s_AST_Node	*cmdline_node;
	struct s_AST_Node	*rootnode;

	job_node = breakjob(node);
	if (job_node == NULL)
		return (NULL);
	if (!term(SEMICOLON, NULL, &node))
	{
		nodedelete(job_node);
		return (NULL);
	}
	cmdline_node = breakcommandline(node);
	if (cmdline_node == NULL)
	{
		nodedelete(job_node);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_SEQ);
	nodesetdata(rootnode, NULL);
	attachbinarybranch(rootnode, job_node, cmdline_node);
	return (rootnode);
}

// check it is semicolon, then move to next node and skip this if statement
// otherwise delete the node and move on
struct s_AST_Node	*breakcommandline2(t_linkedlist *node)
{
	struct s_AST_Node	*job_node;
	struct s_AST_Node	*rootnode;

	job_node = breakjob(node);
	if (job_node == NULL)
		return (NULL);
	if (!term(SEMICOLON, NULL, &node))
	{
		nodedelete(job_node);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_SEQ);
	nodesetdata(rootnode, NULL);
	attachbinarybranch(rootnode, job_node, NULL);
	return (rootnode);
}

struct s_AST_Node	*breakcommandline3(t_linkedlist *node)
{
	return (breakjob(node));
}
