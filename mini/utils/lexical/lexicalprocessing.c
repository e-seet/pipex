#include "../utils.h"

// check that there is a $ char
// if so i mark it. 
// Then proceed on stripping quotes
void	strip_quotes2(char *src, char *dest, int srclen, int *envnum)
{
	int		i;
	char	lastquote;
	int		j;
	char	c;

	j = 0;
	i = 0;
	lastquote = 0;
	while (srclen > i)
	{
		c = src[i];
		if (c == '$')
			*envnum = *envnum + 1;
		if ((c == '\'' || c == '\"') && lastquote == 0)
			lastquote = c;
		else if (c == lastquote)
			lastquote = 0;
		else
			dest[j++] = c;
		i++;
	}
	dest[j] = '\0';
}

// if i found in envp, i replace.
// EG: $HOME = /USERS/..
// New: /USERS/..
// otherwise i dont.
void	replace_to_env(char *src, char **dest, t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], &src[1], ft_strlen(src) - 1) == 0)
		{
			*dest = ft_calloc(ft_strlen(mini->envp[i]) + 1, sizeof(char));
			if (*dest == NULL)
				return (memoryerror(mini));
			ft_strlcpy(*dest, &(mini->envp[i])[ft_strlen(src) - 1],
				ft_strlen(mini->envp[i]) + 1);
			break ;
		}
		i ++;
	}
	if (*dest == NULL)
	{
		*dest = ft_calloc(ft_strlen(src) + 1, sizeof(char));
		if (*dest == NULL)
			return (memoryerror(mini));
		ft_strlcpy(*dest, src, ft_strlen(src) + 1);
	}
}

// go through the argument
// Basically, go through string,
// check if it is end of string or $
// replace it by overwriting if required
void	findenvvariable(char **src, t_mini *mini, int envnum)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	while (*src[i] != '\0')
	{
		if (*src[i] == '$')
		{
			replace_to_env(&(*src)[i], &newstr, mini);
			free(*src);
			*src = newstr;
			envnum = envnum - 1;
		}
		if (envnum == 0)
		{
			break ;
		}
		i ++;
	}
}

// strip quotes.
// Check for $ while stripping
// if it env variable exist,
// replace it
void	strip_quotes(char *src, char **dest, t_mini *mini)
{
	int				srclen;
	int				envnum;

	envnum = 0;
	srclen = ft_strlen(src);
	if (srclen <= 1)
	{
		ft_strlcpy(*dest, src, srclen);
		return ;
	}
	strip_quotes2(src, *dest, srclen, &envnum);
	mini->envnum = envnum;
}

// process double and single quotes
// then process $env
void	lexicalprocess(t_linkedlist *original, t_mini *mini)
{
	t_linkedlist	*node;
	char			*strip;

	node = original;
	while (node != NULL)
	{
		strip = ft_calloc(ft_strlen(original->data) + 1, sizeof(char));
		if (strip == NULL)
			perror("memory allocation failed\n");
		strip_quotes(node->data, &strip, mini);
		free(node->data);
		node->data = strip;
		node = node -> next;
		if (node -> next == NULL)
			break ;
	}
}
