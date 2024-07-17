#include "../utils.h"

// job ; command line
// job ;
// job
// this is the entry leh
struct s_AST_Node	*breakcommandline(t_linkedlist *node, t_mini *mini)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*rootnode;

	saved = node;
	rootnode = breakcommandline1(node, mini);
	if (rootnode != NULL)
		return (rootnode);
	node = saved;
	rootnode = breakcommandline2(node, mini);
	if (rootnode != NULL)
		return (rootnode);
	node = saved;
	rootnode = breakcommandline3(node, mini);
	if (rootnode != NULL)
		return (rootnode);
	return (NULL);
}

// <job>			::=		<command> '|' <job>
// 						|	<command>
struct s_AST_Node	*breakjob(t_linkedlist *node, t_mini *mini)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*rootnode;

	saved = node;
	rootnode = breakjob1(node, mini);
	if (rootnode != NULL)
		return (rootnode);
	node = saved;
	rootnode = breakjob2(node, mini);
	if (rootnode != NULL)
		return (rootnode);
	return (NULL);
}

// <command>		::=
// 					|	<simple command> '<' filename
// 					|	<simple command> '>' filename
/*// 					|	<simple command> '>>' filename */
// 					|	<simple command>
struct s_AST_Node	*breakcommand(t_linkedlist *node, t_mini *mini)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*ast_node;

	saved = node;
	// ast_node = breakcommand1(node, mini);
	// if (ast_node != NULL)
	// 	return (ast_node);
	// node = saved;

	ast_node = breakcommand2(node, mini);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand3(node, mini);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand4(node, mini);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand5(node, mini);
	if (ast_node != NULL)
		return (ast_node);
	return (NULL);
}

// <simple command>::=		<pathname> <token list>
// if (tokenlistnode == NULL)
// {
	// printf("tokenlistnode is null\n");
	// *node = saved;
	// we don't check whether tokenlistnode is NULL since its a valid grammer
// }


struct s_AST_Node	*simplecommand(t_linkedlist **node, t_mini *mini)
{
	struct s_AST_Node	*tokenlistnode;
	struct s_AST_Node	*rootnode;
	char				*path;

	t_linkedlist *original;
	original = *node;

	// if
		tokenlistnode = breakcommand1_modified(node, mini);
		if (tokenlistnode != NULL)
		{
			rootnode = malloc(sizeof(struct s_AST_Node));
			if (rootnode == NULL)
			{
				memoryerror(mini);
				return (NULL);
			}
			nodesettype(rootnode, NODE_CMDPATH);
			// nodesetdata(rootnode, path);
			attachbinarybranch(rootnode, NULL, tokenlistnode);
			return (rootnode);
		}
		else
		{
			*node = original;
			// oriignal
			if (!term(TOKEN, &path, node))
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
			nodesettype(rootnode, NODE_CMDPATH);
			nodesetdata(rootnode, path);
			attachbinarybranch(rootnode, NULL, tokenlistnode);
			return (rootnode);
		}

}

// token
// left null
// right is everything else
// so should do stuff here

// this just return the token list node. Does not have any binary nodes
// <token list>	::=		<token> <token list>
// <token list>	::=		<EMPTY>

struct s_AST_Node	*breaktokenlist(t_linkedlist **node, t_mini *mini)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*rootnode;

	saved = *node;
	
	// rootnode = breakcommand1_modified(node, mini);
	// if (rootnode != NULL)
	// {
	// 	return (rootnode);
	// }
	// *node = saved;
		
	rootnode = tokenlist1(node, mini);
	if (rootnode != NULL)
	{
		return (rootnode);
	}
	*node = saved;
	rootnode = tokenlist2();
	if (rootnode != NULL)
	{
		return (rootnode);
	}
	return (NULL);
}
