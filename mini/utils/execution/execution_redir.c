#include "../utils.h"

// for bckgrnd jobs redirect stdin from /dev/null
void	redirection_async(t_parameters *parameters)
{
	int		fdasync;

	if (parameters->async)
	{
		// printf("is async\n");
		fdasync = open("heredoctemp.txt", O_RDWR);
		if (fdasync == -1)
		{
			perror("heredoctemp.txt failed to open");
			exit(1);
		}
		dup2(fdasync, STDIN_FILENO);
	}
}

void	redirection_fileout(t_parameters *parameters)
{
	int		fdout;

	if (parameters->append == 1)
	{
		fdout = open(parameters->file_out, O_WRONLY | O_CREAT
				| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else
		fdout = open(parameters->file_out, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fdout == -1)
	{
		perror(parameters->file_out);
		exit(1);
	}
	dup2(fdout, STDOUT_FILENO);
}

// read stdin from pipe if present
// write stdout to pipe if present
void	redirection_pipes(t_parameters *parameters)
{
	if (parameters->readpipe)
	{
		printf("read from pipe\n");
		dup2(parameters->piperead, STDIN_FILENO);
	}
	if (parameters->writepipe)
	{
		printf("write to pipe\n");
		dup2(parameters->pipewrite, STDOUT_FILENO);
	}
}

// redirect from background if specified
// redirect stdin from file if specified
// redirect stdout to file if specified
// redirect  from pipe if specified
void	redirection(t_parameters *parameters)
{
	int		fdin;

	redirection_async(parameters);
	if (parameters->file_in)
	{
		fdin = open(parameters->file_in, O_RDONLY);
		if (fdin == -1)
		{
			perror(parameters->file_in);
			printf("fd error\n");
			exit(1);
		}
		dup2(fdin, STDIN_FILENO);
	}
	if (parameters->file_out)
		redirection_fileout(parameters);
	redirection_pipes(parameters);
}
