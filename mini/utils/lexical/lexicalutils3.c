#include "../utils.h"

int	ft_is_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
	{
		return (1);
	}
	return (0);
}

int	returnint(char *str, int i)
{
	if (ft_is_append_output_redirect(&str[i]) == 1)
		return (REDIR);
	else if (ft_is_heredoc_redirect(&str[i]) == 1)
		return (HEREDOC);
	else if (ft_is_output_redirect(&str[i]) == 1)
		return (GREATER);
	else if (ft_is_input_redirect(&str[i]) == 1)
		return (LESSER);
	else if (ft_is_pipe(&str[i]) == 1)
		return (PIPE);
	else
		return (TOKEN);
}

void	move_to_nextnode(t_mini *mini, int strlen, char *str, int i)
{
	t_linkedlist	*newnode;
	int				start;
	t_linkedlist	**node;

	node = &(mini->linkedlist);
	start = 0;
	while (strlen > start)
	{
		(*node)->data[start] = str[(i) + start];
		start ++;
	}
	newnode = malloc(sizeof(t_linkedlist));
	if (newnode == NULL)
		return (memoryerror(mini));
	newnode -> next = NULL;
	(*node)->next = newnode;
	(*node) = (*node)->next;
}

// void	create_node(t_linkedlist **node, char *str, int i, int strlen)
void	create_node(t_mini *mini, char *str, int i, int strlen)
{
	t_linkedlist	**node;

	node = &(mini->linkedlist);
	(*node)->data = ft_calloc(strlen + 1, sizeof(char));
	if ((*node)->data == NULL)
		perror("Memory allocation failed\n");
	(*node)->data[strlen + 1] = '\0';
	i = i - strlen;
	if
	(
		(ft_is_append_output_redirect(&str[i]) == 1)
		|| (ft_is_heredoc_redirect(&str[i]) == 1)
		|| (ft_is_output_redirect(&str[i]) == 1)
		|| (ft_is_input_redirect(&str[i]) == 1)
		|| (ft_is_pipe(&str[i]) == 1)
	)
		(*node)->type = returnint(str, i);
	else
		(*node)->type = TOKEN;
	move_to_nextnode(mini, strlen, str, i);
}

void	free_linkedlist(t_linkedlist *node)
{
	t_linkedlist	*prevnode;

	if (node == NULL)
		return ;
	else
	{
		while (node)
		{
			prevnode = node;
			node = node ->next;
			free(prevnode);
			prevnode = NULL;
		}
		if (prevnode != NULL)
		{
			free(prevnode);
			prevnode = NULL;
		}
	}
}
