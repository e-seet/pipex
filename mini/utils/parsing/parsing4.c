#include "../utils.h"

struct s_AST_Node	*tokenlist1(t_linkedlist **node)
{
	struct s_AST_Node	*tokenlistnode;
	struct s_AST_Node	*rootnode;
	char				*arg;

	if (!term(TOKEN, &arg, node))
	{
		return (NULL);
	}
	tokenlistnode = breaktokenlist(node);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("rootnode malloc error\n");
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
