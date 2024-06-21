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

void	heredocinput(char *input,
	struct s_AST_Node **rootnode, int heredocwritefd)
{
	while (1)
	{
		input = readline(">>:");
		if (input == NULL)
		{
			printf("Ctrl + D pressed outside heredoc\n");
			break ;
		}
		if (input[0] != '\0' || input != NULL)
		{
			// To break
			if (((strncmp(input, (*rootnode)->data, strlen(
								(*rootnode)->data)) == 0) && (strlen(input)
						- linechecker(input)) == strlen((*rootnode)->data)))
			{
				break ;
			}
			write(heredocwritefd, input, ft_strlen(input));
			// write(1,  input, ft_strlen(input));
			free(input);
			input = NULL;
			add_history(input);
		}
		free(input);
	}
}

void	prepheredoc(struct s_AST_Node **rootnode)
{
	int		heredocwritefd;
	char	*input;
	char	*filein;

	heredocwritefd = open("heredoctemp.txt", O_TRUNC
			| O_CREAT | O_RDWR, 0644);
	input = NULL;
	heredocinput(input, rootnode, heredocwritefd);
	if (input != NULL)
		free(input);
	filein = ft_calloc(16, sizeof(char));
	ft_strlcpy(filein, "heredoctemp.txt", ft_strlen("heredoctemp.txt") + 1);
	nodesetdata(*rootnode, filein);
}

// <job>			::=		<command> '|' <job>
// 						|	<command>
// No need of pipes so all 4 parameters are 0
void	execute_job(struct s_AST_Node **rootnode,
	int async, t_parameters *parameters)
{
	if ((*rootnode) == NULL)
		return ;
	if (NODETYPE((*rootnode)->type) == NODE_PIPE)
		execute_pipe((rootnode), async, parameters);
	else if (NODETYPE((*rootnode)->type) == NODE_HEREDOC)
	{
		prepheredoc(rootnode);
		parameters->readpipe = 0;
		parameters->writepipe = 0;
		parameters->piperead = 0;
		parameters->pipewrite = 0;
		parameters->async = async;
		execute_command(rootnode, parameters);
	}
	else
	{
		parameters->readpipe = 0;
		parameters->writepipe = 0;
		parameters->piperead = 0;
		parameters->pipewrite = 0;
		parameters->async = async;
		execute_command(rootnode, parameters);
	}
}