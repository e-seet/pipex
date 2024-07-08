// to do: exit status for set and unset variables (done)
#include "../utils.h"

void	printenv(t_mini *mini)
{
	int	i;

	// 	just env [Based off eval]
	i = 0;
	while (mini->envp[i])
	{
		printf("%s\n", mini->envp[i]);
		i++;
	}
	mini->exit_status = 0;
}

// copy the env over
void	envvariables(t_mini *mini, char *envp[])
{
	int	temp;
	int	i;

	temp = 0;
	i = mini->envplen;
	while (i > temp)
	{
		mini->envp[temp] = ft_calloc(ft_strlen(envp[temp]) + 10, sizeof(char));
		ft_strlcpy(mini->envp[temp], envp[temp], ft_strlen(envp[temp]) + 1);
		temp ++;
	}
}

// export MY_VAR="HELLO"
// check if the variable name already exist
// if so, over ride it
// else continue to copy over the content from existing
void	updateenvvariable_set2(t_mini *mini, int *i, int *found, char **newenvp)
{
	char	**strs;
	char	**strs2;
	char	**strs3;

	strs2 = ft_split(mini->str, ' ');
	strs3 = ft_split(strs2[1], '=');
	while (mini->envplen > (*i))
	{
		strs = ft_split(mini->envp[(*i)], '=');

		if (strs[1] != NULL && (ft_strncmp(strs[0], strs3[0], ft_strlen(strs3[0])) == 0 && ft_strlen(strs3[0]) == ft_strlen(strs[0])) && *found != 1)
		{
			(*found) = 1;
			newenvp[(*i)] = ft_calloc(ft_strlen(strs2[1]) + 1, sizeof(char));
			ft_strlcpy(newenvp[(*i)], strs2[1], ft_strlen(strs2[1]) + 1);
		}
		else
		{
			newenvp[(*i)] = ft_calloc(ft_strlen(mini->envp[(*i)]) + 1,
					sizeof(char));
			ft_strlcpy(newenvp[(*i)], mini->envp[(*i)],
				ft_strlen(mini->envp[(*i)]) + 1);
		}
		free(mini->envp[(*i)]);
		(*i)++;
	}
}

// Set if not present in envp
// Override it if already present
void	updateenvvariable_set(t_mini *mini, char *str)
{
	int		found;
	char	**strs2;
	char	**newenvp;
	int		i;

	strs2 = ft_split(str, ' ');
	newenvp = ft_calloc(mini->envplen + 2, sizeof(char *));
	i = 0;
	found = 0;
	updateenvvariable_set2(mini, &i, &found, newenvp);
	if (found != 1)
	{
		newenvp[i] = ft_calloc(ft_strlen(strs2[1]) + 1, sizeof(char));
		ft_strlcpy(newenvp[i], strs2[1], ft_strlen(strs2[1]) + 1);
		mini->envplen = mini->envplen + 1;
	}
	mini->envp = newenvp;
	mini->exit_status = 0;
}

// // dont over write if it exist 
// // setenv("MY_VARIABLE", "Hello, World!", 0);
// // over write if it exist. BASH DOES THIS
// setenv("MY_VARIABLE", strs[1], 1);

// sample
// export MY_VAR="Hello"
// key, value
// setenv(name, strs[1], 1);

// dont over write if it exist 
// setenv("MY_VARIABLE", "Hello, World!", 0);
// over write if it exist. BASH DOES THIS
// setenv("MY_VARIABLE", strs[1], 1);
void	exportstr(t_mini *mini)
{
	char	**strs;
	// char	*name;
	char	*str;

	str = mini -> str;
	strs = ft_split(str, '=');
	if (!strs[1])
	{
		perror("Thore is no = to split\n");
		free(strs);
		mini->exit_status = 1;
		return ;
	}
	// name = ft_calloc(ft_strlen(strs[0]) - ft_breakspace(strs[0]) + 1,
	// 		sizeof(char));
	// ft_strlcpy(name, &str[ft_breakspace(strs[0])],
	// 	ft_strlen(strs[0]) - ft_breakspace(strs[0]));
	// free(name);
	free(strs);
	updateenvvariable_set(mini, str);
}

// Below is the original code which is not broken down
// to update the current minishell->envp
// will need to reallocate memory space for this.
// void	updateenvvariable_unset(t_mini *mini, char **strs)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**splits;
// 	char	**newenvp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (mini->envplen > i)
// 	{
// 		// split all of them.
// 		splits = ft_split(mini->envp[i], '=');
// 		j = 0;
// 		if (ft_strncmp(splits[0], strs[1], ft_strlen(strs[1])) == 0)
// 		{
// 			// found what i want
// 			// to create new and replace existing
// 			newenvp = ft_calloc(mini->envplen - 1, sizeof(char *));
// 			// copy first haf 
// 			while (i > k)
// 			{
// 				newenvp[k] = ft_calloc(ft_strlen(mini->envp[k]), sizeof(char));
// 				ft_strlcpy(newenvp[k], mini->envp[k], ft_strlen(mini->envp[k]));
// 				free(mini->envp[k]);
// 				k++;
// 			}
// 			// free this particular 1 that we dont want
// 			free(mini->envp[k]);
// 			// continue the op with newenvp being k and 
// 			//minishell data being k + 1
// 			while (mini->envplen > k)
// 			{
// 				newenvp[k] = ft_calloc(
// 						ft_strlen(mini->envp[k + 1]), sizeof(char));
// 				ft_strlcpy(newenvp[k], mini->envp[k + 1],
// 					ft_strlen(mini->envp[k + 1]));
// 				free(mini->envp[k + 1]);
// 				k++;
// 			}
// 			mini->envplen = mini->envplen - 1;
// 			mini->envp = newenvp;
// 			break ;
// 		}
// 		else
// 		{
// 			while (splits[j])
// 			{
// 				free(splits[j]);
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// }
