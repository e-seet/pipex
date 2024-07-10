#include "../utils.h"

// first term is diff
// second term is same
struct s_AST_Node	*breakcommand_node(
	t_linkedlist *node, t_mini *mini,
	int termval, char *filename
	)
{
	struct s_AST_Node	*simplecommand_node;

	simplecommand_node = simplecommand(&node, mini);
	if (simplecommand_node == NULL)
		return (NULL);
	if (!term(termval, NULL, &node))
	{
		nodedelete(simplecommand_node);
		return (NULL);
	}
	if (!term(TOKEN, &filename, &node))
	{
		nodedelete(simplecommand_node);
		free(filename);
		return (NULL);
	}
	return (simplecommand_node);
}

struct s_AST_Node	*tokenlist1(t_linkedlist **node, t_mini *mini)
{
	struct s_AST_Node	*tokenlistnode;
	struct s_AST_Node	*rootnode;
	char				*arg;

	if (!term(TOKEN, &arg, node))
	{
		return (NULL);
	}
	tokenlistnode = breaktokenlist(node, mini);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		memoryerror(mini);
		return (NULL);
	}
	nodesettype(rootnode, NODE_ARGUMENT);
	nodesetdata(rootnode, arg);
	attachbinarybranch(rootnode, NULL, tokenlistnode);
	return (rootnode);
}

struct	s_AST_Node	*tokenlist2(void)
{
	return (NULL);
}
