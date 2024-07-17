#include "../utils.h"

// <<
// /*
struct s_AST_Node	*breakcommand1(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, 1002, &filename);
	if (simplecommand_node == NULL)
		return (NULL);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		memoryerror(mini);
		return (NULL);
	}
	nodesettype(rootnode, NODE_HEREDOC);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

// i want to add this layer at the bottom
struct s_AST_Node	*breakcommand1_modified(t_linkedlist **node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	printf("break command1 modified\n");

	// token is already tested for.

	// printf("modified 1\n");
	// printf("node type(CAT TOKEN):%d\n", (*node)->type);
	// simplecommand_node = simplecommand(node, mini);



	// simplecommand_node = breakcommand_node(*node, mini, 1002, &filename);
	
	simplecommand_node = breaktokenlist(node, mini);
	if (simplecommand_node == NULL)
		return (NULL);
	// if (!term(TOKEN, NULL, &node))
	// {
	// 	nodedelete(simplecommand_node);
	// 	return (NULL);
	// }
	// if (!term(TOKEN, filename, &node))
	// {
	// 	nodedelete(simplecommand_node);
	// 	free(*filename);
	// 	return (NULL);
	// }

	// printf("node type(<< 1002):%d\n", (*node)->type);
	if (!term(1002, NULL, node))
	{
		nodedelete(simplecommand_node);
		return (NULL);
	}
	// printf("node type (EOF TOKEN):%d\n", (*node)->type);
	if (!term(TOKEN, &filename, node))
	{
		nodedelete(simplecommand_node);
		free(filename);
		return (NULL);
	}

	if (simplecommand_node == NULL)
	{
		printf("simplecommand node is null\n");
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		memoryerror(mini);
		return (NULL);
	}

	// printf("make heredoc\n");
	nodesettype(rootnode, NODE_HEREDOC);
	nodesetdata(rootnode, filename);
	printf("filename in 1:%s\n", filename);
	// t_linkedlist *temp = *node;
	// while (temp)
	// {
	// 	// printf("data:%s\n", temp->data);
	// 	// printf("current type:%d\n", temp->type);
	// 	temp = temp->next;
	// }
	// printf("\n\n");

	// printf("set heredoc in breakcommand 3\n");
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	printf("modified 1 worked\n");
	return (rootnode);
}
// */

struct s_AST_Node	*breakcommand2(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, LESSER, &filename);
	if (simplecommand_node == NULL)
		return (NULL);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		memoryerror(mini);
		return (NULL);
	}
	nodesettype(rootnode, NODE_REDIRECT_IN);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

// >>
// to fix the permission for this
// this needs to append and not overwrite like breakcommand4
struct s_AST_Node	*breakcommand3(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, REDIR, &filename);
	if (simplecommand_node == NULL)
		return (NULL);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		memoryerror(mini);
		return (NULL);
	}
	nodesettype(rootnode, NODE_REDIRECT);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

// this did not get called. 
// probably broken with command3 <<
// > 
struct s_AST_Node	*breakcommand4(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, GREATER, &filename);
	if (simplecommand_node == NULL)
		return (NULL);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		memoryerror(mini);
		return (NULL);
	}
	nodesettype(rootnode, NODE_REDIRECT_OUT);
	nodesetdata(rootnode, filename);
	// printf("break command 4\n filename:%s", filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

struct s_AST_Node	*breakcommand5(t_linkedlist *node, t_mini *mini)
{
	return (simplecommand(&node, mini));
}

// <
// struct s_AST_Node	*breakcommand2(t_linkedlist *node, t_mini *mini)
// {
// 	struct s_AST_Node	*simplecommand_node;
// 	char				*filename;
// 	struct s_AST_Node	*rootnode;

// 	filename = NULL;
// 	simplecommand_node = simplecommand(&node, mini);
// 	if (simplecommand_node == NULL)
// 		return (NULL);
// 	if (!term(LESSER, NULL, &node))
// 	{
// 		nodedelete(simplecommand_node);
// 		return (NULL);
// 	}
// 	if (!term(TOKEN, &filename, &node))
// 	{
// 		nodedelete(simplecommand_node);
// 		free(filename);
// 		return (NULL);
// 	}
// 	rootnode = malloc(sizeof(struct s_AST_Node));
// 	if (rootnode == NULL)
// 	{
// 		memoryerror(mini);
// 		return (NULL);
// 	}
// 	nodesettype(rootnode, NODE_REDIRECT_IN);
// 	nodesetdata(rootnode, filename);
// 	attachbinarybranch(rootnode, NULL, simplecommand_node);
// 	return (rootnode);
// }

// // >>
// // to fix the permission for this
// // this needs to append and not overwrite like breakcommand4
// struct s_AST_Node	*breakcommand3(t_linkedlist *node, t_mini *mini)
// {
// 	struct s_AST_Node	*simplecommand_node;
// 	char				*filename;
// 	struct s_AST_Node	*rootnode;

// 	filename = NULL;
// 	simplecommand_node = simplecommand(&node, mini);
// 	if (simplecommand_node == NULL)
// 		return (NULL);
// 	if (!term(REDIR, NULL, &node))
// 	{
// 		nodedelete(simplecommand_node);
// 		return (NULL);
// 	}
// 	if (!term(TOKEN, &filename, &node))
// 	{
// 		nodedelete(simplecommand_node);
// 		free(filename);
// 		return (NULL);
// 	}
// 	rootnode = malloc(sizeof(struct s_AST_Node));
// 	if (rootnode == NULL)
// 	{
// 		memoryerror(mini);
// 		return (NULL);
// 	}
// 	nodesettype(rootnode, NODE_REDIRECT);
// 	nodesetdata(rootnode, filename);
// 	attachbinarybranch(rootnode, NULL, simplecommand_node);
// 	return (rootnode);
// }

// // > 
// struct s_AST_Node	*breakcommand4(t_linkedlist *node, t_mini *mini)
// {
// 	struct s_AST_Node	*simplecommand_node;
// 	char				*filename;
// 	struct s_AST_Node	*rootnode;

// 	filename = NULL;
// 	simplecommand_node = simplecommand(&node, mini);
// 	if (simplecommand_node == NULL)
// 		return (NULL);
// 	if (!term(GREATER, NULL, &node))
// 	{
// 		nodedelete(simplecommand_node);
// 		return (NULL);
// 	}
// 	if (!term(TOKEN, &filename, &node))
// 	{
// 		nodedelete(simplecommand_node);
// 		free(filename);
// 		return (NULL);
// 	}
// 	rootnode = malloc(sizeof(struct s_AST_Node));
// 	if (rootnode == NULL)
// 	{
// 		memoryerror(mini);
// 		return (NULL);
// 	}
// 	nodesettype(rootnode, NODE_REDIRECT_OUT);
// 	nodesetdata(rootnode, filename);
// 	attachbinarybranch(rootnode, NULL, simplecommand_node);
// 	return (rootnode);
// }

// struct s_AST_Node	*breakcommand5(t_linkedlist *node, t_mini *mini)
// {
// 	return (simplecommand(&node, mini));
// }

// struct s_AST_Node	*breakcommand1(t_linkedlist *node, t_mini *mini)
// {
// 	struct s_AST_Node	*simplecommand_node;
// 	char				*filename;
// 	struct s_AST_Node	*rootnode;

// 	// same part
// 	filename = NULL;
// 	simplecommand_node = breakcommand_node(node, mini, 1002, filename);
// 	// simplecommand_node = simplecommand(&node, mini);
// 	// if (simplecommand_node == NULL)
// 	// 	return (NULL);

// 	// // diff
// 	// if (!term(1002, NULL, &node))
// 	// {
// 	// 	nodedelete(simplecommand_node);
// 	// 	return (NULL);
// 	// }

// 	// // same part
// 	// if (!term(TOKEN, &filename, &node))
// 	// {
// 	// 	nodedelete(simplecommand_node);
// 	// 	free(filename);
// 	// 	return (NULL);
// 	// }

// 	// same part
// 	rootnode = malloc(sizeof(struct s_AST_Node));
// 	if (rootnode == NULL)
// 	{
// 		memoryerror(mini);
// 		return (NULL);
// 	}

// 	nodesettype(rootnode, NODE_HEREDOC);
// 	nodesetdata(rootnode, filename);
// 	attachbinarybranch(rootnode, NULL, simplecommand_node);
// 	return (rootnode);
// }
