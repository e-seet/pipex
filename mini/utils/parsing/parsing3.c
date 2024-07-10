#include "../utils.h"

// <<
struct s_AST_Node	*breakcommand1(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, 1002, filename);
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

struct s_AST_Node	*breakcommand2(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, LESSER, filename);
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
	simplecommand_node = breakcommand_node(node, mini, REDIR, filename);
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

// > 
struct s_AST_Node	*breakcommand4(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node(node, mini, GREATER, filename);
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
