#include "../utils.h"

// find the long long path in envp.
// returns a long string of paths
// need to use ft_split to get back the various paths
// ft_split(path + 5, ':');
// 5 to skip the first few characters
char	*findpath(char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = envp[i];
			break ;
		}
		i++;
	}
	if (ft_strncmp("PATH=", path, 5) == 0)
		return (path);
	else
		return (NULL);
}

// paths is to execute a program using execve
// will need to loop through it to find the right bin to execute the command.
void setupstruct(t_mini *mini, char *envp[])
{
	// char *currpwd;

	int i = 0;
	while(envp[i])
	{
		i++;
	}
	mini->envp = ft_calloc(i + 1, sizeof(char *));
	if (mini->envp == NULL)
		return memoryerror(mini);
	i--;
	mini->envplen = i;
	// we set up the env variables here. 
	// need to update whenever we set and unset too
	envvariables(mini, envp); //temp here
	mini->path = findpath(envp);
	mini->paths = ft_split(mini->path + 5, ':');
	// currpwd = ft_calloc(1024, sizeof(char));
	// currpwd = getcwd(currpwd, 1024);
	// mini->currpwd = currpwd;
	// if (!mini->currpwd)
		// printf("error in getting curr pwd");
	// printf("curr pwd: %s\n", mini->currpwd);
	// mini->commandlen = 0;
}

// For Paths and Path
// print if required to know the content
// printf("path:%s\n\n", mini->path);
// int i;
// i = 0;
// while (mini->paths[i])
// {
// 	printf("path%d: %s\n", i, mini->paths[i]);
// 	i++;
// }

char	*findprocesspath(t_mini *mini, t_parameters *parameters)
{
	int		i;
	char	*path;

	i = 0;
	while (mini->paths[i])
	{
		path = ft_strjoin(mini->paths[i], "/");
		mini->path = ft_strjoin(path,
				parameters->argv[0]);
		free(path);
		if (access(mini->path, F_OK) == 0)
			break ;
		free (mini->path);
		mini->path = NULL;
		i++;
	}
	if (mini->path != NULL && access(mini->path, F_OK) == 0)
		return (mini->path);
	else
		return (NULL);
}
