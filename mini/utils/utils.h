#ifndef UTILS_H
# define UTILS_H

# define RED "\033[1;31m"

// libft
# include "../libft/libft.h"
// gnl
# include "../get_next_line/get_next_line.h"

// my structs that is required
// # include "struct.h"

// libraries required
// #include <readline/readline.h>
// #include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>

// extra: To check if allowed libraries
# include <errno.h>
# include <term.h>
# include <curses.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

// #include <readline/readline.h>

// mac os
// #include <editline/readline.h>

//struct
// astree
typedef enum e_NodeType
{
	// 1
	NODE_PIPE			= (1 << 0),
	// 2
	NODE_BCKGRND		= (1 << 1),
	// 4
	NODE_SEQ			= (1 << 2),
	// 8
	// <
	NODE_REDIRECT_IN	= (1 << 3),
	// 16
	// >
	NODE_REDIRECT_OUT	= (1 << 4),
	// 32
	// >>
	// appending
	NODE_REDIRECT		= (1 << 5),
	// 64
	// <<
	NODE_HEREDOC		= (1 << 6),
	// 128
	NODE_CMDPATH		= (1 << 7),
	// 256
	NODE_ARGUMENT		= (1 << 8),
	// 512
	NODE_DATA			= (1 << 9),
}	t_NodeType;

// for lexer below
typedef enum Token
{
	PIPE = '|',
	GREATER = '>',
	LESSER = '<',
	SEMICOLON = ';',
	//unique code for 1001: >> and 1002: <<
	// >>
	REDIR = 1001,
	// <<
	HEREDOC = 1002,
	// CHAR_NULL = 0,
	TOKEN	= -1,
}	t_Token;

struct s_node
{
	char			*data;
	int				type;
	struct s_node	*next;
};
typedef struct s_node			t_linkedlist;

// parser struct
struct s_AST_Node
{
	char				*data;
	int					type;

	struct s_AST_Node	*left;
	struct s_AST_Node	*right;
};
typedef struct s_AST_Node		t_ast_node;

// for execution
struct s_parameters
{
	int		argc;
	char	**argv;
	// whether we need to read
	int		readpipe;
	int		writepipe;

	// the fd to read from
	int		piperead;
	int		pipewrite;
	int		append;
	char	*file_in;
	char	*file_out;
	int		async;
};
typedef struct s_parameters		t_parameters;

// general

// Struct definition for t_mini
struct s_mini
{
	t_linkedlist		*linkedlist;
	t_parameters		*parameters;
	struct s_AST_Node	*ast_node;

	char				*str;

	// for cd -
	char				*prevpwd;

	// for execvp
	char				**paths;
	char				*path;

	// my env variables
	char				**envp;
	// number of env variable
	int					envplen;
	// exe result
	int					exit_status;

	// check the number of $. (basically how many env variable we expecting)
	int					envnum;
};
typedef struct s_mini			t_mini;

// exit_status is for $?
// exit_status -1 means not used / put inside yet.

// execve:
//  0 = success
// -1 = failure
// EACCESS (13): Permission denied.
// ENOENT (2): No such file or directory.
// ENOMEM (12): Out of memory.
// EIO (5): Input/output error.
// EISDIR (21): Is a directory (attempting to execute a directory).
// EINVAL (22): Invalid argument (typically indicates a problem with the executable format or other arguments).

// $? numbers:
// 0: Successful completion. Indicates that the command or script executed without errors.
// 1: General error. This exit status is often used to indicate that a command or script encountered an unspecified error condition.
// 2: Misuse of shell builtins (for example, incorrect syntax).
// 126: Command invoked cannot execute. This typically indicates a permission problem or a non-executable file being attempted to execute.
// 127: Command not found. Indicates that the command invoked was not found in the search path or is not executable.
// 128: Invalid argument to exit. This indicates that the exit command was used incorrectly.
// 130: Script terminated by Control-C. This is the exit status returned when a script is terminated by the user pressing Ctrl+C.
// 255: Exit status out of range. Indicates that the command or script encountered an exit status that was outside the allowable range of 0-255.

// functions

// setup.c
void				setupstruct(t_mini *t_minishell, char *envp[]);
char				*findpath(char *envp[]);
char				*findprocesspath(t_mini *mini, t_parameters *parameters);

// utils.c
void				memoryerror(t_mini *mini);

// setenv.c
// initial
void				printenv(t_mini *mini);
void				envvariables(t_mini *mini, char *envp[]);
// if there export env (setting)
void				exportstr(t_mini *mini);

// unsetenv.c
int					ft_breakspace(char *str);
void				unsetmyenv(t_mini *mini);

// lexical file
t_linkedlist		*lexical(char *str, t_mini *mini);

// lexical processing
void				lexicalprocess(t_linkedlist *original, t_mini *mini);

// lexicalutils
int					ft_is_output_redirect(char *str);
int					ft_is_append_output_redirect(char *str);
int					ft_is_input_redirect(char *str);
int					ft_is_heredoc_redirect(char *str);
int					ft_is_conditional_or(char *str);

// lexicalutils2
int					ft_is_whitespaces(char *str);
int					ft_is_pipe(char *str);
int					ft_is_semicolon(char *str);
int					ft_is_single_quote(char *str);
int					ft_is_double_quote(char *str);
// int				ft_is_double_ampersand(char *str);
// int				ft_is_bracket1(char *str);
// int				ft_is_bracket2(char *str);

// lexicalutils3
int					ft_is_dollar(char *str);
int					returnint(char *str, int i);
// void				move_to_nextnode(t_linkedlist **node);
// void				create_node(t_linkedlist **node,
// 						char *str, int i, int strlen);
void				move_to_nextnode(t_mini *mini, int strlen, char *str, int i);

void				create_node(t_mini *mini,
						char *str, int i, int strlen);

void				free_linkedlist(t_linkedlist *node);

//lexicalprocessing
void				findenvvariable(char **src, t_mini *mini, int envnum);

// top layers
// parsing
struct s_AST_Node	*breakcommandline(t_linkedlist *node);
struct s_AST_Node	*breakjob(t_linkedlist *node);
struct s_AST_Node	*breakcommand(t_linkedlist *node);
struct s_AST_Node	*simplecommand(t_linkedlist **node);

// breakcommandline in parsing1
struct s_AST_Node	*breakcommandline1(t_linkedlist *node);
struct s_AST_Node	*breakcommandline2(t_linkedlist *node);
struct s_AST_Node	*breakcommandline3(t_linkedlist *node);

// break job in parsing2
struct s_AST_Node	*breakjob1(t_linkedlist *node);
struct s_AST_Node	*breakjob2(t_linkedlist *node);

// parsing3.c
// <<
struct s_AST_Node	*breakcommand1(t_linkedlist *node);
// <
struct s_AST_Node	*breakcommand2(t_linkedlist *node);
//>>
struct s_AST_Node	*breakcommand3(t_linkedlist *node);
//>
struct s_AST_Node	*breakcommand4(t_linkedlist *node);
struct s_AST_Node	*breakcommand5(t_linkedlist *node);

// parsing4.c
struct s_AST_Node	*breaktokenlist(t_linkedlist **node);
struct s_AST_Node	*tokenlist1(t_linkedlist **node);
struct	s_AST_Node	*tokenlist2(void);

// parsingutils
struct s_AST_Node	*breakcommandline(t_linkedlist *token);
struct s_AST_Node	*breakjob(t_linkedlist *token);
struct s_AST_Node	*breakcommand(t_linkedlist *token);
struct s_AST_Node	*simplecommand(t_linkedlist **token);
struct s_AST_Node	*breaktokenlist(t_linkedlist **token);

// parsing utils
// void				free_ast(struct s_AST_Node *rootnode);
void				attachbinarybranch(struct s_AST_Node *root,
						struct s_AST_Node *leftnode,
						struct s_AST_Node *rightnode);
void				nodesettype(struct s_AST_Node *node, t_NodeType nodetype);
void				nodesetdata(struct s_AST_Node *node, char *data);
void				nodedelete(struct s_AST_Node *node);
int					term(int type, char **buffer, t_linkedlist **node);

// execute
//executejob
int					linechecker(char *str);
void				heredocinput(char *input,
						struct s_AST_Node **rootnode, int heredocwritefd);
void				prepheredoc(struct s_AST_Node **rootnode, t_mini *mini);
void				execute_job(struct s_AST_Node **rootnode,
						int async, t_parameters *parameters,
						t_mini *mini);

// execute simple command
void				free_parameters(t_parameters *parameters);
void				execute_simple_command(struct s_AST_Node *rootnode,
						t_mini	*mini,
						char	*redirect_in,
						char	*redirect_out
						);
void				execute_command2(struct s_AST_Node **rootnode,
						t_parameters *parameters,
						t_mini *mini);
void				execute_command(struct s_AST_Node **rootnode,
						t_parameters *parameters,
						t_mini	*mini);

// execute.c
void				execute_cmdline(struct s_AST_Node **rootnode,
						t_parameters *parameters,
						t_mini	*mini);
void				execute_syntax_tree(struct s_AST_Node *rootnode,
						t_parameters *parameter,
						t_mini *mini);
// illegal to fix
// # define nodetype(a) (a & (~NODE_DATA))	// get the type of the nodes
int					nodetype(enum e_NodeType type);
void				free_ast(struct s_AST_Node **rootnode,
						struct s_AST_Node *original);

// executepipe.c
void				execute_pipe_job(struct s_AST_Node **rootnode,
						t_parameters *parameters,
						t_mini *mini,
						int fd[]);

void				execute_pipe(struct s_AST_Node **rootnode,
						int async, t_parameters *parameters,
						t_mini *mini);

// execution_redir.c
void				redirection_async(t_parameters *parameters);
void				redirection_fileout(t_parameters *parameters);
void				redirection_pipes(t_parameters *parameters);
void				redirection(t_parameters *parameters);

// executionprep
void				init_command_internal_prep_argv(struct s_AST_Node *rootnode,
						t_parameters *parameters, struct s_AST_Node *argnode,
						int *i);
int					init_command_internal(struct s_AST_Node *rootnode,
						t_parameters *parameters, char *file_in,
						char *file_out);

// execution.c
void				execution2(t_parameters *parameters, t_mini *mini);

// executionbuiltin.c
void				execute_pwd(t_parameters *parameters, t_mini *mini);
// refer to setenv.c (exporting/ set env)
// refer to unsetenv.c (unset env)
// executioncd.c
void				execute_cd(t_parameters *parameters, t_mini *mini);

// void				updatepwd(struct s_minishell *t_minishell);

// struct SigintHandlerParams {
//     int heredoc;
//     int process;
//     // char param2[256]; // Example parameter
// };
// extern struct SigintHandlerParams sigintParams;

// signal.c
extern volatile sig_atomic_t sigint_received;

// typedef union t_CustomUnion
// {
// 	t_linkedlist		data0;
// 	struct s_AST_Node	data1;
// 	// t_parameters		data2;
// }	t_CustomUnion;

void				setsignals(int sig);

// void				setup_signal(
// 						struct sigaction *sa1,
// 						struct sigaction *sa2,
// 						struct sigaction *sa3);
// void				setup_signal1(void);
// void				setup_signal2(void);
// void				setup_signal3(void);

#endif

// top
//parsing
// <command line>	::= 	<job> ';' <command line>
// 					|	<job> ';'
// 						<job>

//parsing2
// <job>			::=		<command> '|' <job>
// 					|	<command>

//parsing
// <command>		::=		<simple command> '<' filename
// 					|	<simple command> '>' filename
// 					|	<simple command> '>>' filename
// 					|	<simple command> '<<' filename
// 					|	<simple command>

//parsing1
// <simple command>::=		<pathname> <token list>

// <token list>	::=		<token> <token list>
// |	(EMPTY)
// bottom
