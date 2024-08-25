#include "../utils.h"

struct s_AST_Node	*breakjob1_node(t_linkedlist **node, t_mini *mini)
{
	struct s_AST_Node	*command_node;

	command_node = breakcommand(node, mini);
	if (command_node == NULL)
	{
		// printf("break command is null\n");
		return (NULL);
	}

	// if (command_node->data != NULL)
	// 	printf("rootnode of breakcommand:%s",((command_node)->data));

	// if (command_node->right->data != NULL)
	// 	printf("rootnode of breakcommand:%s",((command_node)->right->data));

	// if ((command_node->left) != NULL)
	// 	printf("rootnode of breakcommand:%s", ((command_node)->left->data));

	// printf("current node type?: %s To check pipe now[in term]\n",  ((*node)->data));
	if (!term(PIPE, NULL, node))
	{
		// printf("where is the pipe?\n");
		nodedelete(command_node);
		return (NULL);
	}
	return (command_node);
}

// 1. check it is semicolon, then move to next node and skip this if statement
// otherwise delete the node and move on
// 2. Look for the next command line
// if null delete
// <job>			::=		<command> '|' <job>
struct s_AST_Node	*breakjob1(t_linkedlist **node, t_mini *mini)
{
	struct s_AST_Node	*command_node;
	struct s_AST_Node	*job_node;
	struct s_AST_Node	*rootnode;

	// printf("breakjob1\n");
	printf("\nchecking for com|job\n");
	command_node = NULL;
	if ((*node)->data != NULL)
	{
		printf("check for command: %s\n", (*node)->data);
	}
	command_node = breakjob1_node(node, mini);
	if (command_node == NULL)
	{
		printf("comamnd node is null. return!\n");
		return (NULL);
	}
	if ((*node)->data != NULL)
		printf("check for job:%s\n", (*node)->data);
	job_node = breakjob(node, mini);
	if (job_node == NULL)
	{
		printf("jod node is null. return!\n\n");
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
	
	// printf("| happens first\n");
	// printf("traverse left side\n");
	// inOrderTraversal(rootnode->left, 0);

	// printf("traverse right side\n");
	// inOrderTraversal(rootnode->right, 0);



	return (rootnode);
}

// struct s_AST_Node	*breakjobtest(t_linkedlist *node, t_mini *mini)
// {
// 	struct s_AST_Node	*command_node;
// 	struct s_AST_Node	*job_node;
// 	struct s_AST_Node	*rootnode;

// 	command_node = NULL;
// 	command_node = breakjob1_node(node, mini);
// 	if (command_node == NULL)
// 		return (NULL);
	
// 	job_node = breakjob(node, mini);
// 	if (job_node == NULL)
// 	{
// 		nodedelete(job_node);
// 		return (NULL);
// 	}
// 	rootnode = malloc(sizeof(struct s_AST_Node));
// 	if (rootnode == NULL)
// 	{
// 		perror("rootnode malloc error\n");
// 	}
// 	nodesettype(rootnode, NODE_PIPE);
// 	nodesetdata(rootnode, NULL);
// 	attachbinarybranch(rootnode, command_node, job_node);
// 	return (rootnode);
// }

struct s_AST_Node	*breakjob2(t_linkedlist **node, t_mini *mini)
{
	return (breakcommand(node, mini));
}
