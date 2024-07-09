#include "../utils.h"

// this is in child program
int	execution_pwd(t_parameters *parameters, int fd, char *cwd, t_mini *mini)
{
	if (parameters->file_out)
	{
		fd = open(parameters->file_out, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			perror(parameters->file_out);
			return (5);
		}
		dup2(fd, STDOUT_FILENO);
	}
	if (parameters->writepipe)
		dup2(parameters->pipewrite, STDOUT_FILENO);
	if (getcwd(cwd, 4096) != NULL)
	{
		write(STDOUT_FILENO, ft_strjoin(cwd, "\n"), strlen(cwd) + 1);
		free(cwd);
		return (0);
	}
	else
	{
		perror("getcwd() error");
		mini -> exit_status = 2;
		return (2);
	}
}

// parent to wait for child process
void	execution_pwd_parent_wait(int pid, char *cwd, t_mini *mini)
{
	int	wpid;

	wpid = 0;
	while (wpid <= 0)
	{
		if (waitpid(pid, &wpid, 0) == -1)
		{
			mini -> exit_status = 1;
			break ;
		}
		else
			mini -> exit_status = 0;
	}
	free(cwd);
	if ((wpid & 0xFF) == 0)
		mini->exit_status = (wpid >> 8) & 0xFF;
}

// double check this
// should process the child more

// checking on which exit status to store
// the child or the parent
void	execute_pwd(t_parameters *parameters, t_mini *mini)
{
	pid_t	pid;
	int		fd;
	char	*cwd;
	int		result;

	fd = 0;
	cwd = ft_calloc(4096, sizeof(char));
	if (cwd == NULL)
		return (memoryerror(mini));
	pid = fork();
	if (pid == 0)
	{
		result = execution_pwd(parameters, fd, cwd, mini);
		if (parameters->file_out && fd != STDOUT_FILENO)
			close(fd);
		exit(result);
	}
	else if (pid < 0)
	{
		perror("fork");
		mini -> exit_status = 1;
		free(cwd);
	}
	else
		execution_pwd_parent_wait(pid, cwd, mini);
}

// void updatepwd(struct s_minishell *t_minishell)
// {
// 	char *currpwd;

// 	currpwd = ft_calloc(1024, sizeof(char));

// 	currpwd = getcwd(currpwd, 1024);
// 	if (t_minishell->currpwd != NULL)
// 	{
// 		free(t_minishell->currpwd);
// 	}
// 	t_minishell->currpwd = currpwd;
// 	if (!t_minishell->currpwd)
// 		printf("error in getting curr pwd");

// 	// printf("curr pwd: %s\n", t_minishell->currpwd);
// }

// void changedirectory(char *str, struct s_minishell *t_minishell)
// {
// 	printf("str:%s", str);

// 	// back to home directory
// 	// "cd "
// 	// The home directory can be retrieved by: echo $HOME
// 	if (ft_strncmp(str, "cd ", ft_strlen("cd ") == 0))
// 	{
// 	}
// 	else if (ft_strncmp(str, "cd ~", ft_strlen("cd ~") == 0))
// 	{
// 	
// 		// tilde as a shortcut to home directory
// 		// cd ~/Document
// 	}
// 	else if (ft_strncmp(str, "cd -", ft_strlen("cd -")) == 0)
// 	{
// 		// back to the previous directory that i was in
// 		// cd -
// 		if (chdir(t_minishell->prevpwd) != 0)
// 		{
// 			printf("Error navigating to:%s", t_minishell->prevpwd);
// 			perror("chdir: change directory error\n");
// 		}
// 		else
// 		{
// 			t_minishell->prevpwd = t_minishell->currpwd;

// 			char *currpwd;
// 			currpwd = ft_calloc(1024, sizeof(char));
// 			currpwd = getcwd(currpwd, 1024);
// 			t_minishell->currpwd = currpwd;
// 		}			
// 	}
// 	else
// 	{
// 		printf("else\n");
// 		// go up 1 level
// 		// "cd .."
// 		char **temp;
// 		char *dir;

// 		temp = ft_split(str, ' ');
// 		// printf("temp[1]:%s\n\n", temp[1]);
// 		dir = ft_calloc(ft_strlen(temp[1]) + 1, sizeof(char));

// 		ft_strlcpy(dir, temp[1], ft_strlen(temp[1]));

// 		printf("cd %s\n", dir);

// 		if (chdir(dir) != 0)
// 		{
// 			printf("Error navigating to:%s", dir);
// 			perror("chdir: change directory error\n");
// 		}
// 		else
// 		{
// 			t_minishell->prevpwd = t_minishell->currpwd;

// 			char *currpwd;
// 			currpwd = ft_calloc(1024, sizeof(char));
// 			currpwd = getcwd(currpwd, 1024);
// 			t_minishell->currpwd = currpwd;
// 		}
// 		// Works
// 		// "cd ." // does nothing .. so ignore

// 		// change to absolute / relative directory
// 		// more exmaples
// 		// Relative Paths
// 		// cd ../
// 		// cd ../../
// 		// cd ../42
// 		// remain in same directory
// 		// cd ./ 
// 		// cd ./anotherfile.txt
// 		// cd /Users/eddieseet/MDesktop/Curr/minishell/utils
// 		// cd /Users/eddieseet/MDesktop
// 		// cd /bin
// 		// cd /etc/hosts

// 		// not sure if required.
// 		// export CDPATH=.:~/Documents
// 		// cd directory_name
// 	}

// }