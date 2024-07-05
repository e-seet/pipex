#include "../utils.h"

// <<
struct s_AST_Node	*breakcommand1(t_linkedlist *node)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	simplecommand_node = simplecommand(&node);
	if (simplecommand_node == NULL)
		return (NULL);
	if (!term(1002, NULL, &node))
	{
		nodedelete(simplecommand_node);
		return (NULL);
	}
	filename = NULL;
	if (!term(TOKEN, &filename, &node))
	{
		nodedelete(simplecommand_node);
		free(filename);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_HEREDOC);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

// <
struct s_AST_Node	*breakcommand2(t_linkedlist *node)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	simplecommand_node = simplecommand(&node);
	if (simplecommand_node == NULL)
		return (NULL);
	if (!term(LESSER, NULL, &node))
	{
		nodedelete(simplecommand_node);
		return (NULL);
	}
	filename = NULL;
	if (!term(TOKEN, &filename, &node))
	{
		nodedelete(simplecommand_node);
		free(filename);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_REDIRECT_IN);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

// >>
// to fix the permission for this
// this needs to append and not overwrite like breakcommand4
struct s_AST_Node	*breakcommand3(t_linkedlist *node)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	simplecommand_node = simplecommand(&node);
	if (simplecommand_node == NULL)
		return (NULL);
	if (!term(REDIR, NULL, &node))
	{
		nodedelete(simplecommand_node);
		return (NULL);
	}
	filename = NULL;
	if (!term(TOKEN, &filename, &node))
	{
		nodedelete(simplecommand_node);
		free(filename);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_REDIRECT);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

// > 
struct s_AST_Node	*breakcommand4(t_linkedlist *node)
{
	struct s_AST_Node	*simplecommand_node;
	char				*filename;
	struct s_AST_Node	*rootnode;

	simplecommand_node = simplecommand(&node);
	if (simplecommand_node == NULL)
		return (NULL);
	if (!term(GREATER, NULL, &node))
	{
		nodedelete(simplecommand_node);
		return (NULL);
	}
	filename = NULL;
	if (!term(TOKEN, &filename, &node))
	{
		nodedelete(simplecommand_node);
		free(filename);
		return (NULL);
	}
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
	}
	nodesettype(rootnode, NODE_REDIRECT_OUT);
	nodesetdata(rootnode, filename);
	attachbinarybranch(rootnode, NULL, simplecommand_node);
	return (rootnode);
}

struct s_AST_Node	*breakcommand5(t_linkedlist *node)
{
	return (simplecommand(&node));
}
