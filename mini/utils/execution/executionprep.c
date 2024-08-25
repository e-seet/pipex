#include "../utils.h"

void	init_command_internal_prep_argv(struct s_AST_Node *rootnode,
		t_parameters *parameters, struct s_AST_Node *argnode, int *i)
{
	printf("\n\n\n>>>>init_command_internal_prep_argv\n");
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
	while
	(
		argnode != NULL && (nodetype(argnode->type) == NODE_ARGUMENT
			|| nodetype(argnode->type) == NODE_CMDPATH)
	)
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

	int check = 0;
	
	while (parameters->argv[check])
	{
		printf("check:%d, %s\n", check, parameters->argv[check]);
		check ++;
	}


}

// !!important
// maybe should change this.
// if there is pipe, there is no file output.
// my file_out should be to pipe and not eof.
// Therefore i should change from parameters to mini
int	init_command_internal(struct s_AST_Node *rootnode,
	t_mini *mini,
	char *file_in, char *file_out)
{
	int					i;
	struct s_AST_Node	*argnode;
	

	if (rootnode == NULL || !(nodetype(rootnode->type) == NODE_CMDPATH))
	{
		mini->parameters->argc = 0;
		printf("return -1 in internal\n");
		return (-1);
	}
	argnode = rootnode;
	i = 0;
	init_command_internal_prep_argv(rootnode, mini->parameters, argnode, &i);
	if (i == 0)
	{
		mini->parameters->argv[0] = (char *)malloc(ft_strlen(argnode->data) + 1);
		if (mini->parameters->argv[0] == NULL)
		{
			perror("Malloc parameters argv failed\n");
		}
		ft_strlcpy(mini->parameters->argv[0], argnode->data,
			ft_strlen(argnode->data) + 1);
	}
	mini->parameters->argc = i;
	mini->parameters->argv[i] = NULL;

	if (file_in != NULL)
		mini->parameters->file_in = file_in;

	if ((mini->parameters->pipe != 1) && (file_out != NULL))
	{
		printf("here set file out!\n");
		mini->parameters->file_out = file_out;
	}
	return (0);
}
