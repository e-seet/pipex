#include "../utils.h"

void	attachbinarybranch(struct s_AST_Node *root,
	struct s_AST_Node *leftnode, struct s_AST_Node *rightnode)
{
	if (root != NULL)
	{
		root->left = leftnode;
		root->right = rightnode;
	}
}

void	nodesettype(struct s_AST_Node *node, t_NodeType nodetype)
{
	if (node != NULL)
		node->type = nodetype;
}

// void	nodeoverridedata(struct s_AST_Node *node, char *data)
// void	nodeoverridedata(struct s_AST_Node *rootnode)
// {
// 	char	*filein;
// 	filein = ft_calloc(16, sizeof(char));
// 	ft_strlcpy(filein, "heredoctemp.txt", ft_strlen("heredoctemp.txt") + 1);
// 	if (rootnode->data != NULL)
// 	{
// 		free(rootnode->data);
// 	}
// 	nodesetdata(rootnode, filein);
// }

void	nodesetdata(struct s_AST_Node *node, char *data)
{
	if (node != NULL)
	{
		if (data != NULL)
		{
			node->data = data;
			node->type |= NODE_DATA;
		}
		else
			node->data = NULL;
	}
}

void	nodedelete(struct s_AST_Node *node)
{
	if (node == NULL)
		return ;
	if (node->type & NODE_DATA)
		free(node->data);
	nodedelete(node->left);
	nodedelete(node->right);
	free(node);
}

int	term(int type, char **buffer, t_linkedlist **node)
{
	if ((*node) == NULL)
		return (0);
	if ((*node)->type == type)
	{
		if (buffer != NULL)
		{
			*buffer = malloc(ft_strlen((*node)->data) + 1);
			if (*buffer == NULL)
			{
				perror("rootnode malloc error\n");
			}
			ft_strlcpy(*buffer, (*node)->data, ft_strlen((*node)->data) + 1);
		}
		(*node) = (*node)->next;
		return (1);
	}
	(*node) = (*node)->next;
	return (0);
}
