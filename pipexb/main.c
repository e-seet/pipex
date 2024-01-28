#include "utils.h"

int	p3child(char *envp[], struct s_pipex pipexstruct)
{
	int		execveresult;

	pipexstruct.path = findprocesspath(pipexstruct, 3);
	if (access(pipexstruct.path, F_OK) != 0)
	{
		perror("command not found");
		return (1);
	}
	execveresult = execve(pipexstruct.path, pipexstruct.argvs3, envp);
	if (execveresult == -1)
		perror("smth wrong with executing. Terminate now");
	free(pipexstruct.path);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct s_pipex	pipexstruct;

	if (pipe(pipexstruct.fdpipe1) == -1 || pipe(pipexstruct.fdpipe2) == -1)
		return (1);
	setstructure(argc, argv, &pipexstruct, envp);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (heredoccmd(&pipexstruct) == 0)
		{
			pipexstruct.heredocreadfd = open("heredoctemp.txt", O_RDONLY);
			if (pipexstruct.heredocreadfd == -1)
				perror("heredocreadfd opened with error\n");
		}
		else
			perror("heredoccmd failed. Nothing inside\n");
	}
	while (pipexstruct.argc - 1 > pipexstruct.curr)
	{
		pipexstruct.argvs3 = ft_split(argv[pipexstruct.curr], ' ');
		if (pipexstruct.curr != 3 && pipexstruct.curr % 2 == 1)
		{
			if (pipe(pipexstruct.fdpipe1) == -1)
				return (1);
		}
		else if (pipexstruct.curr != 4 && pipexstruct.curr % 2 == 0)
		{
			if (pipe(pipexstruct.fdpipe2) == -1)
				return (1);
		}
		pipexstruct.pid3 = fork();
		if (pipexstruct.pid3 == 0)
		{
			if (pipexstruct.curr == 3)
			{
				dup2(pipexstruct.p1fd, 0);
				dup2(pipexstruct.fdpipe1[1], 1);
			}
			else if (pipexstruct.argc - 2 == pipexstruct.curr)
			{
				dup2(pipexstruct.fdpipe2[0], 0);
				dup2(pipexstruct.p2fd, 1);
			}
			else if (pipexstruct.curr % 2 == 0)
			{
				dup2(pipexstruct.fdpipe1[0], 0);
				dup2(pipexstruct.fdpipe2[1], 1);
			}
			else if (pipexstruct.curr % 2 == 1)
			{
				dup2(pipexstruct.fdpipe2[0], 0);
				dup2(pipexstruct.fdpipe1[1], 1);
			}
			if (p3child(envp, pipexstruct) == 1)
				perror("Error with p3child\n");
		}
		else
		{
			if (pipexstruct.curr % 2 == 1)
				close(pipexstruct.fdpipe1[1]);
			else if (pipexstruct.curr % 2 == 0)
				close(pipexstruct.fdpipe2[1]);
			else
				exit(1);
			waitpid(pipexstruct.pid3, NULL, 0);
		}
		pipexstruct.curr += 1;
	}
	return (0);
}

//  ./pipex "here_doc" "END" "tr a b" "tr b c" "tr c d" "output_file"
