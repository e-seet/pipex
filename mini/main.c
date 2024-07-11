#include "utils/utils.h"

volatile sig_atomic_t sigint_received = 0;

void	free_arraypointers(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i ++;
	}
	strs[i] = NULL;
}

// may have segfault
// free parameters(parameters);
void	free_mini(t_mini *mini)
{
	printf("\nfree mini: Linkedlist\n");
	if (mini->linkedlist)
		free_linkedlist(mini->linkedlist);
	printf("free ast\n");
	if (mini->ast_node)
		free_ast(&mini->ast_node, mini->ast_node);
	printf("free parameters\n");
	if (mini->parameters)
		free_parameters(mini->parameters);
	
	// to check if i want to free the below
	// if (mini->str)
	// 	free(mini->str);
	// if (mini->prevpwd)
	// 	free(mini->prevpwd);
	// if (mini->path)
	// 	free(mini->path);
	// if (mini->envp)
	// 	free_arraypointers(mini->envp);
	// if (mini->envp)
	// 	free_arraypointers(mini->paths);
}

// starts the program and get the input from user.
int	checkforexit(char *envp[])
{
	char				*str;

	t_linkedlist		*node;
	struct s_AST_Node			*ast_node;
	t_parameters		*parameters;
	t_mini				*mini;

	//setup 
	printf("\033[1;31m\n");

	str = NULL;
	node = NULL;
	ast_node = NULL;
	
	// Allocate memory for t_mini and its components
	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
		memoryerror(mini);

	parameters = malloc(sizeof(t_parameters));
	if (parameters == NULL)
		memoryerror(mini);
	parameters->argv = NULL;
	parameters->file_in = NULL;
	parameters->file_out = NULL;
	

	mini->linkedlist = node;
	mini->ast_node = ast_node;
	mini->parameters = parameters;
	
	mini->paths = NULL;
	mini->path = NULL;
	mini->envp = NULL;

	mini->prevpwd = NULL;
	mini->str = NULL;
	mini->exit_status = -1;
	// mini->envnum = 0;
	
	
	// this set up mini
	setupstruct(mini, envp);

	// initialize_readline();
	rl_clear_history();

	// setup signal here
    // struct sigaction sa1;
	// struct sigaction sa2;
    // struct sigaction sa3;
    // // int		use_sig_handler;

	// // Flag to switch between handler1 and handler2
	// // use_sig_handler = 1;  

	// // setup_signal(&sa1, &sa2, &sa3);
	// setup_signal1(&sa1);
    
	// either or
	// sigaction(SIGINT, &sa1, NULL);

	setsignals(0);

	// Change from top:
	while (1)
	{
		str = readline("minishell>");
		if (!str)
			break;
		if (*str)
			add_history(str);

		// sigint
		if (sigint_received == -1
			// || sigint_received == 2
			|| sigint_received == -3
			)
		{
			printf("sigint received: %d", sigint_received);
			printf("free both\n");
			free_mini(mini);
			printf("reset to 0\n");
			if (sigint_received == -3)
				exit(0);
			sigint_received = 0;
		}

		// To do: Check the first 2
        
		// not using this if statement??
		if (strcmp(str, "reset_hist") == 0)
		{
            // Reset the history if 'reset_hist' command is entered
			rl_clear_history();
            printf("History cleared.\n");
        }
		else
		{
            // Handle other commands
            // printf("You entered: %s\n", str);
			mini -> str = str;
			// if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
			// {
				// if just env [Based off eval]
				// int i = 0;
				// while (t_minishell->envp[i])
				// {
				// 	printf("%s\n", t_minishell->envp[i]);
				// 	i++;
				// }

				// if there are other commands EG:
				// 1.Run command with modified env
				// env VAR1=foo VAR2=bar command
				// 2.Modify the env for shell session
				// env Path=$PATH:/new/path
				// 3.Print value of specific env
				// env | grep PATH
				// 4. execute command with clean env
				// env -i command
				// 5. setting env variable for a command
				// env -u VAR1 -i VAR2=value command

			// }
			// Export and set don't really need clean up since they are more or less fixed
			// eg: Export MY_VAR="smth" || unset MY_VAR
			// else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
			// {
			// 	// export to env
			// 	// exportstr(str, t_minishell);	
			// }
			// else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
			// {
			// 	// unset a variable in the env
			// 	// unsetmyenv(str, t_minishell);
			// }
			// else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) ==0)
			// {
			// 	// updatepwd(t_minishell);
			// 	// printf("%s\n", t_minishell->currpwd);
			// }
			// else if (ft_strncmp(str, "cd", ft_strlen("cd")) ==0)
			// {
			// 	// changedirectory(str, t_minishell);
			// }
			// else
			// {
				// token_list token_list;
				
				// set up signal

				printf("lexical\n");
				node = lexical(str, mini);// this return a linked list
				// // pass the linked list into the parser

				t_linkedlist *templist;
				templist = node;
				while(templist)
				{
					printf("templist:%s\n", templist->data);
					templist = templist -> next;

				}


				printf("parsing\n");
				ast_node = breakcommandline(node, mini);

				printf("execution\n");
				execute_syntax_tree(ast_node, parameters, mini);

				// sigint
				if (sigint_received == -1
					// || sigint_received == 2
					// || sigint_received == 3
					)
				{
					// printf("sigint received: %d\n", sigint_received);
					free_mini(mini);
					printf("reset to 0\n");
					sigint_received = 0;
				}
				else
				{
					free_mini(mini);
					node = NULL;
					ast_node = NULL;
				}

				// free ast_nodes inside execution.c

			// }
        }

        rl_on_new_line(); // Prepare readline for new input
		// this should comment out
        // rl_redisplay(); // Redisplay the line (useful if line was replaced)
        
        free(str); // Free the input string allocated by readline
	}
	rl_clear_history();

	return (0);
}

/*
1. i will also need some kind of mechanism to expand env
eg: $abc = /root/eseet/...
i need to be able to expand $abc

So what do i really need? to handle?
""
''
$

2. Handle extra quotations and all when it is just a single string.

3.remove quotes from words / things not interfered with seperators

4. Bonus: Handle *
*/

int main(int argc, char *argv[], char *envp[])
{
	// printf("argv:%d %p\n",argc, argv[0]);
	if (argc == 1)
	{
		if (ft_strncmp("./minishell", argv[0], 11) == 0)
		{
			checkforexit(envp);
		}
	}
	return (0);
}