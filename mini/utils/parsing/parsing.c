#include "../utils.h"

// job ; command line
// job ;
// job
// this is the entry leh
struct s_AST_Node	*breakcommandline(t_linkedlist *node)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*rootnode;

	saved = node;
	rootnode = breakcommandline1(node);
	if (rootnode != NULL)
		return (rootnode);
	node = saved;
	rootnode = breakcommandline2(node);
	if (rootnode != NULL)
		return (rootnode);
	node = saved;
	rootnode = breakcommandline3(node);
	if (rootnode != NULL)
		return (rootnode);
	return (NULL);
}

// <job>			::=		<command> '|' <job>
// 						|	<command>
struct s_AST_Node	*breakjob(t_linkedlist *node)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*rootnode;

	saved = node;
	rootnode = breakjob1(node);
	if (rootnode != NULL)
		return (rootnode);
	node = saved;
	rootnode = breakjob2(node);
	if (rootnode != NULL)
		return (rootnode);
	return (NULL);
}

// <command>		::=		<simple command> '<' filename
// 					|	<simple command> '>' filename
// 					|	<simple command> '>>' filename
// 					|	<simple command> '<<' filename
// 					|	<simple command>
struct s_AST_Node	*breakcommand(t_linkedlist *node)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*ast_node;

	saved = node;
	ast_node = breakcommand1(node);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand2(node);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand3(node);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand4(node);
	if (ast_node != NULL)
		return (ast_node);
	node = saved;
	ast_node = breakcommand5(node);
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
struct s_AST_Node	*simplecommand(t_linkedlist **node)
{
	struct s_AST_Node	*tokenlistnode;
	struct s_AST_Node	*rootnode;
	char				*path;

	if (!term(TOKEN, &path, node))
	{
		return (NULL);
	}
	tokenlistnode = breaktokenlist(node);
	rootnode = malloc(sizeof(struct s_AST_Node));
	if (rootnode == NULL)
	{
		perror("malloc error\n");
	}
	nodesettype(rootnode, NODE_CMDPATH);
	nodesetdata(rootnode, path);
	attachbinarybranch(rootnode, NULL, tokenlistnode);
	return (rootnode);
}

// this just return the token list node. Does not have any binary nodes
// <token list>	::=		<token> <token list>
// <token list>	::=		<EMPTY>

struct s_AST_Node	*breaktokenlist(t_linkedlist **node)
{
	t_linkedlist		*saved;
	struct s_AST_Node	*rootnode;

	saved = *node;
	rootnode = tokenlist1(node);
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
