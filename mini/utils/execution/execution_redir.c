#include "../utils.h"

// Make a copy of fd, and read
// This will not work if it is reading from pipe FD.
// Because after reading, the pipe data will be gone.
void read_fd_data(int fdin)
{
	// Duplicate the file descriptor
	int fd_copy = dup(fdin);
	if (fd_copy == -1) {
		perror("Error duplicating file descriptor");
		close(fdin);
		exit(1);
	}
	// Read from the duplicated descriptor
	char buffer[256];
	ssize_t bytes_read = read(fd_copy, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
	{
		perror("Error reading file");
	}
	else
	{
		buffer[bytes_read] = '\0'; // Null-terminate the string
		printf("File content read from duplicated fd:\n%s\n", buffer);
	}
	// Close the duplicated descriptor
	close(fd_copy);
	printf("\n");
}

// for bckgrnd jobs redirect stdin from /dev/null
void	redirection_async(t_parameters *parameters)
{
	int		fdasync;

	printf("\n>>redirect_ async\n");
	// if there is a heredoc, we open that file and read
	if (parameters->heredoc)
	{
		// printf("is async\n");
		fdasync = open("heredoctemp.txt", O_RDWR);
		if (fdasync == -1)
		{
			perror("heredoctemp.txt failed to open");
			exit(1);
		}
		printf("opened heredoc temp as fd");
		// change stdin to heredoc fd
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
	printf("\n>>redirection_pipes: in and out~~\n");
	int fdin;

	// Flag to write to pipe
	if (parameters->writepipe > 0)
	{
		printf("writepipe(to write 0/1): %d\n", parameters->writepipe);
		// printf("check the piperead:%d and pipewrite:%d\n", parameters->piperead, parameters->pipewrite);

		// If the filein is heredoc file
		if (ft_strncmp(parameters->file_in, "heredoctemp.txt", ft_strlen("heredoctemp.txt")) == 0)
		{

			fdin = open(parameters->file_in, O_RDONLY);
			if (fdin == -1)
			{
				perror(parameters->file_in);
				printf("fd error\n");
				exit(1);
			}
			else
			{
				printf("changing from pipewrite to fdin!!!!!!!!\n");
		  	
				char buffer[1024];
				ssize_t bytes_read;
				while ((bytes_read = read(fdin, buffer, sizeof(buffer))) > 0)
				{
					// write into pipe
					if (write(parameters->pipewrite, buffer, bytes_read) == -1) {
						perror("write to pipe");
						close(fdin);
						exit(1);
					}
				}
				if (bytes_read == -1)
				{
					perror("read"); x
				}
			
				// Close fdin after duplication
    			close(fdin);
				// Close pipewrite if you're done writing
				close(parameters->pipewrite);
				
			}
		}
		// if no file to read from. Just write
		else
		{
			dup2(parameters->pipewrite, STDOUT_FILENO);
		}
	}

	if (parameters->readpipe > 0)
	{
		close(parameters->pipewrite);
		
		// printf("readpipe(to read 0/1): %d\n", parameters->readpipe);
		// close(parameters->piperead);
		// printf("check the piperead:%d and pipewrite:%d\n", parameters->piperead, parameters->pipewrite);
		
		// printf("content of pipe read:!!\n");
		// int copy;
		// copy = dup(parameters->piperead);
		// read_fd_data(parameters->piperead);
		// read_fd_data(copy);

		// copy = dup(parameters->piperead);
		// read_fd_data(copy);
		printf("to read from pipe isntead | but i not printing the fd out\n");
		dup2(parameters->piperead, STDIN_FILENO);
		
		//got data
		// read_fd_data(parameters->piperead);
		
		//got data also
		// read_fd_data(STDIN_FILENO);
	}


	// if (parameters->readpipe > 0)
	// {
	// 	printf("read from pipe\n\n\n\n");
	// 	dup2(parameters->piperead, STDIN_FILENO);
	// }	

	// if (parameters->writepipe > 0)
	// {
	// 	printf("write to pipe\n");
	// 	dup2(parameters->pipewrite, STDOUT_FILENO);
	// }
}

// redirect from background if specified
// redirect stdin from file if specified
// redirect stdout to file if specified
// redirect  from pipe if specified
void	redirection(t_parameters *parameters)
{
	int		fdin;

	printf("\n>>redirection\n");
	redirection_async(parameters);

	printf("check parameters file in and out\n");
	if (parameters->file_in)
	{
		printf("file in now here:");
		printf("%s\n", parameters->file_in);
		fdin = open(parameters->file_in, O_RDONLY);
		if (fdin == -1)
		{
			perror(parameters->file_in);
			printf("fd error\n");
			exit(1);
		}

		// TEMP !!
		// read_fd_data(fdin);
		//end of temp

		dup2(fdin, STDIN_FILENO);
	}
	if (parameters->pipe != 1 && parameters->file_out)
	{
		printf("file out now\n");
		redirection_fileout(parameters);
	}
	redirection_pipes(parameters);
}
