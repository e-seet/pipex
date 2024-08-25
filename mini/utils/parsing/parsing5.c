#include "../utils.h"

// What we are doing here is to check and 
// settle to redirection for the heredoc.

// < 60
// > 62
// 1001: >>
// 1002 : heredoc
struct s_AST_Node	*breakcommand1_extend(t_linkedlist **node, t_mini *mini)
{
	char				*filename;
	struct s_AST_Node	*rootnode;
	// int					tokentype;

	filename = NULL;
	// printf("data:%s\n", node->data);
	// printf("type:%d\n", node->type);

	t_linkedlist *saved;
	saved = *node;

	// >>
	if (term(REDIR, NULL, node))
	{
		// printf("data1:%s\n", node->data);
		// printf("type1:%d\n\n", node->type);

		if (!term(TOKEN, &filename, node))
		{
			free(filename);
			return (NULL);
		}
		rootnode = malloc(sizeof(struct s_AST_Node));
		if (rootnode == NULL)
		{
			memoryerror(mini);
			return (NULL);
		}
		nodesettype(rootnode, NODE_REDIRECT);
		nodesetdata(rootnode, filename);
		return (rootnode);
	}

	*node = saved;
	// printf("data:%s\n", node->data);
	// printf("type:%d\n", node->type);
	// >
	if (term(GREATER, NULL, node))
	{
		// printf("data2:%s\n", node->data);
		// printf("type2:%d\n\n", node->type);

		if (!term(TOKEN, &filename, node))
		{
			free(filename);
			return (NULL);
		}
		rootnode = ft_calloc(1,sizeof(struct s_AST_Node));
		if (rootnode == NULL)
		{
			memoryerror(mini);
			return (NULL);
		}
		// find out why the value diff..
		nodesettype(rootnode, NODE_REDIRECT_OUT);
		// printf("root type:%d\n", rootnode->type);
		nodesetdata(rootnode, filename);
		return (rootnode);
	}

	// what about pipe?
	// case 1
	// rootnode = breakcommand(node, mini);
	// if (rootnode != NULL)
	// {
	// 	return rootnode;
	// }
	// else
	// 	return NULL;
	
	// this be recognised as the file out.
	// so does not work.. 
	// printf("check the current node before i do breakjob\n");
	// printf("node:%s", (*node)->data);
	// rootnode = breakjob(*node, mini);
	// if (rootnode != NULL)
	// {
	// 	return rootnode;
	// }
	// else
	// 	return NULL;


	// test pipe here.!! 
	//cat << eof | wc -l
	// cat << eof | grep "abc"

	// < does not exist. So we can just ignore
	// // printf("data:%s\n", node->data);
	// // printf("type:%d\n", node->type);
	// // <
	// if (term(LESSER, NULL, &node))
	// {
	// 	// printf("data3:%s\n", node->data);
	// 	// printf("type3:%d\n\n", node->type);

	// 	if (!term(TOKEN, &filename, &node))
	// 	{
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
	// 	return (rootnode);
	// }

	return NULL;
}

struct s_AST_Node	*breakcommand2_extend(t_linkedlist **node, t_mini *mini)
{
	struct s_AST_Node	*rootnode;
	// t_linkedlist		*saved;
	
	// what if i use breakjob()
	// saved = *node;
	// *node = saved;
	
	// printf("breakcommand2_extend function here\n");
	if ((*node) != NULL)
	{
		printf("node data:%s\n", (*node)->data);
	}
	else if ((*node) == NULL)
	{
		printf("node is null\n");
	}

	if (term(PIPE, NULL, node))
	{
		// printf("data2:%s\n", node->data);
		// printf("type2:%d\n\n", node->type);
		// printf("found pipe in extend2\n");
		if (!term(TOKEN, NULL, node))
		{
			// free(filename);
			return (NULL);
		}
		rootnode = ft_calloc(1,sizeof(struct s_AST_Node));
		if (rootnode == NULL)
		{
			memoryerror(mini);
			return (NULL);
		}
		// find out why the value diff..
		// nodesettype(rootnode, NODE_PIPE);
		// printf("root type:%d\n", rootnode->type);
		// nodesetdata(rootnode, filename);
		return (rootnode);
	}
	else
	{
		printf("didnt see pipe, return from extend2\n");
		if ((*node) != NULL)
		{
			printf("node data:%s\n", (*node)->data);
		}
		else if ((*node) == NULL)
		{
			printf("node is null\n");
		}
		return NULL;
	}
	//end of pipe
}
