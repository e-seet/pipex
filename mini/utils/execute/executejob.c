#include "../utils.h"

//check if the last character is a \n and subtract accordingly
// go to the position before \0 and check if it is a \n
int	linechecker(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		return (1);
	else
		return (0);
}

// probably need a flag to show that heredoc should be break
void	heredocinput(char *input,
	struct s_AST_Node **rootnode, int heredocwritefd)
{
	// while (1 && sigint_received != -1)
	while (sigint_received != -1)
	{
		input = readline(">>:");
		if (input == NULL)
			break ;
		if (input[0] != '\0' || input != NULL)
		{
			if (((strncmp(input, (*rootnode)->data, strlen(
								(*rootnode)->data)) == 0) && (strlen(input)
						- linechecker(input)) == strlen((*rootnode)->data)))
			{
				free(input);
				rl_clear_history();
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();

				break ;
			}
			write(heredocwritefd, input, ft_strlen(input));
			add_history(input);
			free(input);
			input = NULL;
		}
		free(input);
	}
}

void	prepheredoc(struct s_AST_Node **rootnode, t_mini *mini)
{
	int		heredocwritefd;
	char	*input;
	char	*filein;

	heredocwritefd = open("heredoctemp.txt", O_TRUNC
			| O_CREAT | O_RDWR, 0644);
	input = NULL;
	setsignals(2);
	heredocinput(input, rootnode, heredocwritefd);
	if (sigint_received == -1)
	{
		printf("exit prepheredoc\n");
		return ;
	}
	if (input != NULL)
		free(input);
	
	// here we can control file in. but we do not have the file out
	
	filein = ft_calloc(16, sizeof(char));
	if (filein == NULL)
		return memoryerror(mini);
	ft_strlcpy(filein, "heredoctemp.txt", ft_strlen("heredoctemp.txt") + 1);
	nodesetdata(*rootnode, filein);
}

// <job>			::=		<command> '|' <job>
// 						|	<command>
// No need of pipes so all 4 parameters are 0
void	execute_job(struct s_AST_Node **rootnode,
	int async, t_parameters *parameters, t_mini *mini)
{
	printf("\n00execute_job function\n");
	printf("check if it is pipe or heredoc\n");

	if ((*rootnode) == NULL)
	{
		printf("root node is null in execute_job. weird\n");
		return ;
	}
	
	if (nodetype((*rootnode)->type) == NODE_PIPE)
	{
		printf("1.execute pipe \n");
		execute_pipe((rootnode), async, parameters, mini);
	}
	else if (nodetype((*rootnode)->type) == NODE_HEREDOC)
	{
		printf("1.. prep heredoc stuff\n");
		prepheredoc(rootnode, mini);
		// printf("root type is heredoc\n");
		// printf("check file anme:%s\n", (*rootnode)->data);
		if (sigint_received == -1)
			return ;		



		// execute_command(rootnode, parameters, mini);
		// should split to 2 type after heredoc

		// type1: just redirect to file
		// NODE_REDIRECT | NODE_REDIRECT_OUT
		if (
			((*rootnode)->left != NULL)
			&&
			(((nodetype(((*rootnode)->left)->type)) == NODE_REDIRECT)
			||
			((nodetype(((*rootnode)->left)->type)) == NODE_REDIRECT_OUT))
		)
		{
			parameters->readpipe = 0;
			parameters->writepipe = 0;
			parameters->piperead = 0;
			parameters->pipewrite = 0;
			parameters->async = 0;// why?
			parameters->heredoc = 1;// why?

			printf("node->left not null\n\n\n\n\n");
			parameters->append = 1;
			if (nodetype(((*rootnode)->left)->type) != NODE_REDIRECT)
				parameters->append = 0;

			// if this is a file, then this is fine
			execute_simple_command(((*rootnode)->right),
				mini, (*rootnode)->data, ((*rootnode)->left)->data);

			// execute_command(rootnode, parameters, mini);
		}
		else
		{
			//type2: Not redirection into a file
		 	// so things like pipe / normal command

			// to do here
			// parameters->readpipe = 0;
			// parameters->writepipe = 0;
			// parameters->piperead = 0;
			// parameters->pipewrite = 0;
			// parameters->async = 0;// why?
			// parameters->heredoc = 1;// why?

			// the current rootnode will contain the file-in which is the name of the file, 
			// where o wrote herdoc to

			printf("\n\n\n\n\n");
			printf("else other stuff in hereodc\n");
			// printf("TO DO!!");
			// printf("to do for pipe and what not\n");

			// printf("check traversal \n");
			// inOrderTraversal(*rootnode, 0);

			printf("running simple command \n");
			execute_simple_command(((*rootnode)->right),
						mini, (*rootnode)->data, NULL);

		}
		// type 2: got other commands? pipe?

			// printf("\nhmm. Got other stuff?\n");
			// if ((*rootnode)->left != NULL)
			// {
			// 	printf("hmm2\n");

			// 	// left
			// 	// command 2
			// 	execute_command(&((*rootnode)->left), parameters, mini);
			// 	// right
			// 	// command 1
			// 	execute_command(&((*rootnode)->right), parameters, mini);
			// }
			// else
			// {
			// 	// command 1
			// 	// only right
			// 	execute_command(&((*rootnode)->right), parameters, mini);
			// }


	}
	// else if not pipe / heredoc. Normal execution
	else
	{
		printf("else in execute_job\n");
		parameters->readpipe = 0;
		parameters->writepipe = 0;
		parameters->piperead = 0;
		parameters->pipewrite = 0;
		parameters->async = async;
		parameters->heredoc = 0;
		execute_command(rootnode, parameters, mini);
	}
}
