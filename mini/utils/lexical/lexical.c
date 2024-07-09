#include "../utils.h"

// To do: Clean up memory issues for lexical along with lexical utils3.

// (cd .. && pwd) && pwd >> file
// Check for sepeartor, if found. Add to list.
// > : ft_is_output_redirect
// <  :ft_is_input_redirect
// >> : ft_is_append_output_redirect
// << ft_is_heredoc_redirect
// || ft_is_conditional_or
// | ft_is_pipe
// && ft_is_double_ampersand
// ( ft_is_bracket1
// ) ft_is_bracket2

// ^ type: token
// ^ type: Char INT

void	ft_breakup_str4(char *str, int *i, t_mini *mini, int *counter)
{
	if (ft_is_whitespaces(&str[(*i)]) == 1)
	{
		if ((*counter) > 0)
		{
			create_node(mini, str, (*i), (*counter));
			(*counter) = 0;
		}
		(*i)++;
	}
	else
	{
		(*i)++;
		(*counter)++;
	}
}

// > or < or |
void	ft_breakup_str3(char *str, int *i, t_mini *mini, int *counter)
{
	if (
		(ft_is_output_redirect(&str[(*i)]) == 1)
		|| (ft_is_input_redirect(&str[(*i)]) == 1)
		|| (ft_is_pipe(&str[(*i)]) == 1)
	)
	{
		if ((*counter) > 0)
		{
			create_node(mini, str, (*i), (*counter));
			create_node(mini, str, (*i) + 1, 1);
			(*counter) = 0;
		}
		else
		{
			create_node(mini, str, (*i) + 1, 1);
		}
		(*i)++;
	}
	else
	{
		ft_breakup_str4(str, i, mini, counter);
	}
}

void	ft_breakup_str2(char *str, int *i, t_mini *mini, int *counter)
{
	if (
		(ft_is_append_output_redirect(&str[(*i)]) == 1)
		|| (ft_is_heredoc_redirect(&str[(*i)]) == 1)
	)
	{
		if ((*counter) > 0)
		{
			create_node(mini, str, (*i), (*counter));
			create_node(mini, str, (*i) + 2, 2);
			(*counter) = 0;
		}
		else
		{
			create_node(mini, str, (*i) + 2, 2);
		}
		(*i) = (*i) + 2;
	}
	else
		ft_breakup_str3(str, i, mini, counter);
}

// >> or << 
t_linkedlist	*ft_breakup_str(char *str, t_mini *mini)
{
	int				i;
	int				counter;
	t_linkedlist	*node;
	t_linkedlist	*head;

	i = 0;
	counter = 0;
	head = malloc(sizeof(t_linkedlist));
	if (head == NULL)
		memoryerror(mini);
	head->next = NULL;
	node = head;
	mini->linkedlist = node;
	while (str[i] != '\0')
	{
		ft_breakup_str2(str, &i, mini, &counter);
	}
	if (counter > 0)
		create_node(mini, str, i, counter);
	return (head);
}

t_linkedlist	*lexical(char *str, t_mini *mini)
{
	t_linkedlist	*node;

	node = ft_breakup_str(str, mini);
	lexicalprocess(node, mini);
	return (node);
}

// int	returnint(char *str, int i)
// {
// 	if (ft_is_append_output_redirect(&str[i]) == 1)
// 		return (REDIR);
// 	else if (ft_is_heredoc_redirect(&str[i]) == 1)
// 		return (HEREDOC);
// 	else if (ft_is_output_redirect(&str[i]) == 1)
// 		return (GREATER);
// 	else if (ft_is_input_redirect(&str[i]) == 1)
// 		return (LESSER);
// 	else if (ft_is_pipe(&str[i]) == 1)
// 		return (PIPE);
// 	else
// 		return (TOKEN);
// }

// void	create_node(t_linkedlist **node, char *str, int i, int strlen)
// {
// 	int				start;

// 	start = 0;
// 	(*node)->data = ft_calloc(strlen + 1, sizeof(char));
// 	(*node)->data[strlen + 1] = '\0';
// 	i = i - strlen;
// 	if (
// 		(ft_is_append_output_redirect(&str[i]) == 1)
// 		|| (ft_is_heredoc_redirect(&str[i]) == 1)
// 		|| (ft_is_output_redirect(&str[i]) == 1)
// 		|| (ft_is_input_redirect(&str[i]) == 1)
// 		|| (ft_is_pipe(&str[i]) == 1)
// 	)
// 		(*node)->type = returnint(str, i);
// 	else
// 		(*node)->type = TOKEN;
// 	while (strlen > start)
// 	{
// 		(*node)->data[start] = str[(i) + start];
// 		start ++;
// 	}
// 	move_to_nextnode(node);
// }

// void	ft_strip_quote2(char *str, char *dest, int n, int i)
// {
// 	char	lastquote;
// 	int		j;
// 	char	c;

// 	lastquote = 0;
// 	j = 0;
// 	while (n > i)
// 	{
// 		c = str[i];
// 		if ((c == '\'' || c == '\"') && lastquote == 0)
// 			lastquote = c;
// 		else if (c == lastquote)
// 			lastquote = 0;
// 		else
// 			dest[j++] = c;
// 		i++;
// 	}
// 	dest[j] = '\0';
// }

// void	ft_strip_quote(char *str, char *dest)
// {
// 	int		n;
// 	int		i;

// 	i = 0;
// 	n = ft_strlen(str);
// 	if (n <= 1)
// 	{
// 		ft_strlcpy(dest, str, n);
// 		return ;
// 	}
// 	ft_strip_quote2(str, dest, n, i);
// }

// t_linkedlist	*token;
// token = node;

// char	*string;
// while (token != NULL)
// {
// 	if (token->type == TOKEN)
// 	{
// 		string = malloc(ft_strlen(token->data) + 1);
// 		ft_strip_quote(token->data, string);
// 		free(token->data);
// 		token->data = string;
// 	}
// }
// printf("%p", node);
