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

void	move_to_nextnode(t_linkedlist **node)
{
	t_linkedlist	*newnode;

	newnode = malloc(sizeof(t_linkedlist));
	if (newnode == NULL)
	{
		perror("node malloc error\n");
	}
	newnode -> next = NULL;
	(*node)->next = newnode;
	(*node) = (*node)->next;
}

void	create_node(t_linkedlist **node, char *str, int i, int strlen)
{
	int		start;

	start = 0;
	(*node)->data = ft_calloc(strlen + 1, sizeof(char));
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
	while (strlen > start)
	{
		(*node)->data[start] = str[(i) + start];
		start ++;
	}
	// printf("the data:%s, %p\n", (*node)->data, (*node));
	move_to_nextnode(node);
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
		free(prevnode);
		prevnode = NULL;
	}
}
