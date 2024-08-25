#include "../utils.h"

// <job>			::=		<command> '|' <job>
// left node pipe to right node
// the number 1 and 0 signifies whether we need the pipe read and write
void	execute_pipe(struct s_AST_Node **rootnode,
	int async, t_parameters *parameters, t_mini *mini)
{
	printf("~~execute_pipe.\n");
	int					fd[2];

	pipe(fd);
	parameters->readpipe = 0;
	parameters->writepipe = 1;
	parameters->piperead = fd[0];
	parameters->pipewrite = fd[1];
	parameters->async = async;
	parameters->pipe	= 1;

	// printf("async value:%d\n", parameters->async);
	printf("2. execute_command first.\n\n");
	

	// The following if else handles the left side of the AST.


	// if there is (>>)
	// ?? to check this case
	if
	(
		((*rootnode)->left != NULL) 
		&&
		((nodetype(((*rootnode)->left)->type)) == NODE_REDIRECT)
	)
	{
		printf("this should not be possible because this should be the extreme left side\n");
		printf("and this is the first command when i do my switch cases\n");
		execute_command(&((*rootnode)->left), parameters, mini);
	}

	// if it is heredoc
	else if (
		// nodetype((&((*rootnode)->left))->type == NODE_HEREDOC)
		((*rootnode)->left != NULL)
		&&
		((nodetype(((*rootnode)->left)->type)) == NODE_HEREDOC)
	)
	{
		// this runs
		printf("pipe, found heredoc on the left ~~\n");
		printf("execute job with left node\n\n\n")	;
		
		// check this. option 1
		execute_job(&((*rootnode)->left), async, parameters, mini);

		// Option2 may not be needed with the option 1 running ok.
		// command
		// execute_command(&((*rootnode)->left), parameters, mini);
	}
	// ALL OTHER CASES
	else
	{
		printf("else cases: Run this\n");
		execute_command(&((*rootnode)->left), parameters, mini);
	}
	printf("\n\n\n3.execute_pipe_job now | SETTLE RIGHT SIDE OF NODE\n");
	execute_pipe_job(rootnode, parameters, mini, fd);
}

// right side of the pipe.
void	execute_pipe_job(struct s_AST_Node **rootnode,
	t_parameters *parameters, t_mini *mini, int fd[])
{
	struct s_AST_Node	*jobnode;

	printf("execute pipe job\n");
	
	// Get the first node on right
	jobnode = (*rootnode)->right;

	// Continue executing everything on the right side
	while (jobnode != NULL && nodetype(jobnode->type) == PIPE)
	{
		close(parameters->pipewrite);
		pipe(fd);
		parameters->pipewrite = fd[1];
		parameters->readpipe = 1;
		parameters->writepipe = 1;
		execute_command(&((*rootnode)->left), parameters, mini);
		close(parameters->piperead);
		parameters->piperead = fd[0];
		jobnode = jobnode -> right;
	}
	parameters->piperead = fd[0];
	close(parameters->pipewrite);
	parameters->readpipe = 1;
	parameters->writepipe = 0;
	execute_command(&((*rootnode)->right), parameters, mini);
	close(parameters->piperead);
}
