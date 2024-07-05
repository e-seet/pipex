#include "../utils.h"

void	init_command_internal_prep_argv(struct s_AST_Node *rootnode,
		t_parameters *parameters, struct s_AST_Node *argnode, int *i)
{
	while (argnode != NULL && (!(nodetype(argnode->type) == NODE_ARGUMENT)
			|| !(nodetype(argnode->type) == NODE_CMDPATH)))
	{
		argnode = argnode->right;
		(*i)++;
	}
	if ((*i) == 0)
	{
		printf("i = 0; type:%d \n", argnode->type);
		parameters->argv = (char **)malloc(sizeof(char *) * (1 + 1));
		if (parameters->argv == NULL)
		{
			perror("Malloc parameters argv failed\n");
		}
	}
	else
	{
		parameters->argv = (char **) malloc(sizeof(char *) * ((*i) + 1));
		if (parameters->argv == NULL)
		{
			perror("Malloc parameters argv failed\n");
		}
	}
	argnode = rootnode;
	(*i) = 0;
	while (
		argnode != NULL && (nodetype(argnode->type) == NODE_ARGUMENT
			|| nodetype(argnode->type) == NODE_CMDPATH))
	{
		parameters->argv[*i] = (char *)malloc(ft_strlen(argnode->data) + 1);
		if (parameters->argv[*i] == NULL)
		{
			perror("Malloc parameters argv failed\n");
		}
		ft_strlcpy(parameters->argv[*i], argnode->data,
			ft_strlen(argnode->data) + 1);
		argnode = argnode->right;
		(*i)++;
	}
}

int	init_command_internal(struct s_AST_Node *rootnode,
	t_parameters *parameters, char *file_in, char *file_out)
{
	int					i;
	struct s_AST_Node	*argnode;

	if (rootnode == NULL || !(nodetype(rootnode->type) == NODE_CMDPATH))
	{
		parameters->argc = 0;
		printf("return -1 in internal\n");
		return (-1);
	}
	argnode = rootnode;
	i = 0;
	init_command_internal_prep_argv(rootnode, parameters, argnode, &i);
	if (i == 0)
	{
		parameters->argv[0] = (char *)malloc(ft_strlen(argnode->data) + 1);
		if (parameters->argv[0] == NULL)
		{
			perror("Malloc parameters argv failed\n");
		}
		ft_strlcpy(parameters->argv[0], argnode->data,
			ft_strlen(argnode->data) + 1);
	}
	parameters->argc = i;
	parameters->argv[i] = NULL;
	parameters->file_in = file_in;
	parameters->file_out = file_out;
	return (0);
}
