#include "../utils.h"

void	free_parameters(t_parameters *parameters)
{
	int	i;

	// printf("to check where i am doing freeing of parameters\n");
	i = 0;
	while (parameters->argc > i)
	{
		free(parameters->argv[i]);
		parameters->argv[i] = NULL;
		i++;
	}
	free(parameters->argv);
	parameters->argv = NULL;
	parameters->argc = 0;
	if (parameters->file_in)
	{
		free(parameters->file_in);
		parameters->file_in = NULL;
	}
	if (parameters->file_out)
	{
		free(parameters->file_out);
		parameters->file_out = NULL;
	}
}

void	execute_simple_command(struct s_AST_Node *rootnode,
							t_mini	*mini,
							char	*redirect_in,
							char	*redirect_out
							)
{
	int	errors;

	errors = init_command_internal(rootnode, mini->parameters,
			redirect_in, redirect_out);
	if (errors == 0)
	{
		execution2(mini->parameters, mini);
	}
}

void	execute_command2(struct s_AST_Node **rootnode,
	t_parameters *parameters, t_mini *mini)
{
	if (nodetype((*rootnode)->type) == NODE_REDIRECT)
	{
		parameters->append = 1;
		execute_simple_command(((*rootnode)->right),
			mini, NULL, (*rootnode)->data);
	}
	else if (nodetype((*rootnode)->type) == NODE_REDIRECT_OUT)
	{
		parameters->append = 0;
		execute_simple_command(((*rootnode)->right),
			mini, NULL, (*rootnode)->data);
	}
	else
	{
		parameters->append = 0;
		execute_simple_command((*rootnode), mini, NULL, NULL);
	}
}

// 5 main cases
void	execute_command(struct s_AST_Node **rootnode,
	t_parameters *parameters, t_mini *mini)
{
	if ((*rootnode) == NULL)
	{
		printf("root node is null");
		return ;
	}
	if (nodetype((*rootnode)->type) == NODE_HEREDOC)
	{
		parameters->append = 1;
		
		// this part may need to execute first.
		if ((*rootnode)->left != NULL)
		{
			printf("type:%d\n", nodetype(((*rootnode)->left)->type));
			printf("fileout:%s\n", ((*rootnode)->left)->data);
			if (nodetype(((*rootnode)->left)->type) != NODE_REDIRECT)
				parameters->append = 0;
			
			execute_simple_command(((*rootnode)->right),
				mini, (*rootnode)->data, ((*rootnode)->left)->data);
		}
		else
		{
			execute_simple_command(((*rootnode)->right),
				mini, (*rootnode)->data, NULL);
		}
	}
	else if (nodetype((*rootnode)->type) == NODE_REDIRECT_IN)
	{
		parameters->append = 0;
		execute_simple_command(((*rootnode)->right),
			mini, (*rootnode)->data, NULL);
	}
	else
	{
		execute_command2(rootnode, parameters, mini);
	}
}
