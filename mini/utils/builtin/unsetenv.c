#include "../utils.h"

int	ft_breakspace(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len --)
	{
		if (str[len] == ' ')
		{
			break ;
		}
	}
	return (len);
}

// Found the variable
// update the envp accordingly
// copy first half, then second half
void	updateenvvariable_unset2(t_mini *mini, int *i)
{
	int		k;
	char	**newenvp;

	k = 0;
	newenvp = ft_calloc(mini->envplen - 1, sizeof(char *));
	while ((*i) > k)
	{
		newenvp[k] = ft_calloc(ft_strlen(mini->envp[k]) + 1, sizeof(char));
		ft_strlcpy(newenvp[k], mini->envp[k], ft_strlen(mini->envp[k]) + 1);
		free(mini->envp[k]);
		k++;
	}
	free(mini->envp[k]);
	while (mini->envplen - 1 > k)
	{
		newenvp[k] = ft_calloc(
				ft_strlen(mini->envp[k + 1]) + 1, sizeof(char));
		ft_strlcpy(newenvp[k], mini->envp[k + 1],
			ft_strlen(mini->envp[k + 1]) + 1);
		free(mini->envp[k + 1]);
		k++;
	}
	mini->envplen = mini->envplen - 1;
	mini->envp = newenvp;
}

// remove from envp
// if found , remove it and update envp
// strs[1] is the key
void	updateenvvariable_unset(t_mini *mini, char **strs)
{
	int		i;
	int		j;
	char	**splits;

	i = 0;
	j = 0;
	while (mini->envplen > i)
	{
		splits = ft_split(mini->envp[i], '=');
		j = 0;
		if (ft_strncmp(splits[0], strs[1], ft_strlen(strs[1])) == 0 && ft_strlen(strs[1]) == ft_strlen(splits[0]))
		{
			updateenvvariable_unset2(mini, &i);
			break ;
		}
		else
		{
			while (splits[j])
			{
				free(splits[j]);
				j++;
			}
		}
		i++;
	}
}

// this is to set on actual env
// unsetenv(strs[1]);
// unset MY_VAR
void	unsetmyenv(t_mini *mini)
{
	char	**strs;

	strs = ft_split(mini->str, ' ');
	if (!strs[1])
		perror("missing variable name\n");
	updateenvvariable_unset(mini, strs);
	mini->exit_status = 0;
}
