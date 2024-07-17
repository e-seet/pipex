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
				break ;
			}
			write(heredocwritefd, input, ft_strlen(input));
			free(input);
			input = NULL;
			add_history(input);
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
	if ((*rootnode) == NULL)
		return ;
	if (nodetype((*rootnode)->type) == NODE_PIPE)
		execute_pipe((rootnode), async, parameters, mini);
	
	else if (nodetype((*rootnode)->type) == NODE_HEREDOC)
	{
		printf("root type is heredoc\n");
		prepheredoc(rootnode, mini);
		if (sigint_received == -1)
			return ;
		parameters->readpipe = 0;
		parameters->writepipe = 0;
		parameters->piperead = 0;
		parameters->pipewrite = 0;
		parameters->async = 1;
		execute_command(rootnode, parameters, mini);
	}
	else
	{
		parameters->readpipe = 0;
		parameters->writepipe = 0;
		parameters->piperead = 0;
		parameters->pipewrite = 0;
		parameters->async = async;
		execute_command(rootnode, parameters, mini);
	}
}
