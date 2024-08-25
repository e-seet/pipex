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
	printf("\n>>execute_simple_command\n");

	printf("type of rootnode%d\n", nodetype((*rootnode).type));

	if (redirect_in != NULL)
	{
		printf("redirect in :%s\n", redirect_in);

	}
	if (redirect_out != NULL)
		printf("redirect out :%s\n", redirect_out);
	
	errors = init_command_internal(rootnode, (mini),
			redirect_in, redirect_out);

	// normal process & there is no errors
	if (errors == 0)
	{
		execution2(mini->parameters, mini);
	}
}












// sorting
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
// sorting
void	execute_command(struct s_AST_Node **rootnode,
	t_parameters *parameters, t_mini *mini)
{
	printf("0execute_command\n");
	if ((*rootnode) == NULL)
	{
		printf("root node is null\n\n");
		return ;
	}

	if (nodetype((*rootnode)->type) == NODE_HEREDOC)
	{
		printf("\nfound heredoc in execute_command\n");
		parameters->append = 1;

		// there is a place to output file
		if ((*rootnode)->left != NULL)
		{
			// printf("type:%d\n", nodetype(((*rootnode)->left)->type));
			// printf("fileout:%s\n", ((*rootnode)->left)->data);
			printf("normal heredoc executes here\n");

			if (nodetype(((*rootnode)->left)->type) != NODE_REDIRECT)
				parameters->append = 0;
			
			// if this is a file, then this is fine
			execute_simple_command(
				((*rootnode)->right),
				mini, 
				(*rootnode)->data, 
				((*rootnode)->left)->data);

		}

		else
		{
			// no output redirection specified
			// scenario 1: no output to push to
			// scenario 2: pipe
			if ((*rootnode)->right != NULL)
			{
				printf("execute simple command? for some reason; HEREDOC ISSUE!!\n\n\n\n");

				// this in under heredoc alr
				// there is pipe
				if (parameters->pipe == 1)
				{
					printf("pipe == 1\n");
					//HERE IS THE ISSUE
					// this creates issue where i am looking at EOF only.
					// right is eof
					// left is null.
					// if pipe, there is no file out too

					execute_simple_command(
						((*rootnode)->right),
						mini, 
						(*rootnode)->data,
						// ((*rootnode)->left)->data
						NULL
						);
				}
				else
				{
					// to test
					// may cause issues
					printf("pipe 1!= 1\n");
					execute_simple_command(((*rootnode)->right),
					mini, (*rootnode)->data, NULL);

				}

			}
			
		}
	}

	// Afterwards if there is redirect in
	// may cause issues
	if (nodetype((*rootnode)->type) == NODE_REDIRECT_IN)
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
