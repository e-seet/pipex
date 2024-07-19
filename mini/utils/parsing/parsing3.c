#include "../utils.h"

// <<
// /*
struct s_AST_Node	*breakcommand1(t_linkedlist *node, t_mini *mini)
{
	struct s_AST_Node	*simplecommand_node;
	struct s_AST_Node	*redirection_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	filename = NULL;
	simplecommand_node = breakcommand_node_1(&node, mini, 1002, &filename);
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

	// let's say that is is not the end
	// i should be able to get where it is being redirected to
	// printf("data:%s\n", node->data);
	// printf("type:%d\n", node->type);
	redirection_node = breakcommand1_extend(node, mini);

	if (redirection_node != NULL)
	{
		attachbinarybranch(rootnode, redirection_node, simplecommand_node);
	}
	else
		attachbinarybranch(rootnode, NULL, simplecommand_node);

	return (rootnode);
}
// */

// <
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
	printf("break command 4\n filename:%s", filename);
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
