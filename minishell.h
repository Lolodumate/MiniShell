/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:19:44 by laroges           #+#    #+#             */
/*   Updated: 2024/03/13 16:24:34 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
• Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
• Handle "" (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
 
Ressources :
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6
https://www.youtube.com/watch?v=ubt-UjcQUYg

*/

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum	e_bool
{
	FALSE,
	TRUE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
	PIPE,
	DOLLAR,
	AMPERSAND,
	NOTOKEN
}		t_bool;

typedef struct	s_data
{
	
}		t_data;

// Describes a simple command and arguments
typedef struct	s_simple_cmd
{
	int	nb_of_available_arg; // Available space for arguments currently preallocated
	int	nb_arg; // Number of arguments
	char	**args; // Array of arguments
//	s_simple_cmd(); // ?
//	void	insert_arg(char *arg); // ?
}		t_simple_cmd;

// Describes a complete command with the multiple pipes if any. And input/output redirection if any.
typedef struct	s_cmd
{
	int	nb_of_available_simple_cmd;
	int	nb_of_simple_cmd;
//	t_simple_cmd **simple_cmd;
	char	*outfile;
	char	*infile;
	char	*errfile;
	int	background;
//	void	prompt();
//	void	print();
//	void	execute();
//	void	clear();
//	s_cmd(); // ?
//	void	insert_simple_cmd(t_simple_cmd *simple_cmd);
//	static struct	s_cmd	*current_cmd;
//	static	t_simple_cmd *current_simple_cmd;
}		t_cmd;

// Prompt and history
void	prompt(int argc, char **argv, char **envp);

//__________________________________________________________________________________________________________________________________________
// Lexer
	// A Lexer takes the input characters and put them together into words called tokens, and a parser that processes the tokens according to a grammar and build the command table.	
	// The tokens are described in a file shell.l.
	// The file shell.l is processed with a program called LEX that generates the lexical analyzer.

//__________________________________________________________________________________________________________________________________________
// Parser
	// The parser reads the command line and puts it into a data structure called COMMAND TABLE that will store the commands that will be executed.
		// !!! Entrer toutes les lignes de commandes dans une table.
	// The grammar rules used by the parser are described in a file called shell.y.
	// shell.y is processed by a program called YACC that generates a parser program.

//__________________________________________________________________________________________________________________________________________
// Expander

//__________________________________________________________________________________________________________________________________________
// Grammar
	// Need to implement GRAMMAR in shell.l and shell.y to make the parser interpret the command lines and provide the executor with the correct information.
	// GRAMMAR :
	// cmd[arg]* [|cmd[arg]*]*
	// 	[[>filename][<filename][>&filename][>>filename][>>&filename]]*[&]
	// cmd is the command followed by 0 or more arguments (arg).
	// this command and its argument can be followed by another subcommand (also followed by 0 or more arguments) represented with a pipe.
	// [>filename] means that there might be 0 or 1 >filename redirections.
	// The [&] at the end means that the & character is optionnal.
		// !!! The parser takes the tokens and check if they follow the syntax described by the grammar rules in shell.y.
//__________________________________________________________________________________________________________________________________________
// Command table
	//


//__________________________________________________________________________________________________________________________________________
// Executor
	// 1. Take the COMMAND TABLE.
	// 2. Create a new process for each SIMPLE COMMAND in the array.
	// 3. If necessary, create pipes to communicate the ouput of a process to the input of the next one. And it will redirect the standard input, standard output and standard error when there are any redirections.
	// Creating new processes : start by CREATING A NEW PROCESS FOR EACH COMMAND in the pipeline and making the parent wait for the last command. This will allowe running simple commands such as "ls -al".
void	exec_command(char *input);

//__________________________________________________________________________________________________________________________________________
// Handle characters
int	is_metacharacter(char *c); // To handle : < << > >> | $ 

//__________________________________________________________________________________________________________________________________________

// Clean memory
void	free_str(char **str);


/*
 ******************************************		SYNTAXE SHELL			****************************************************

	* Shell command language : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
    The shell reads its input from a file (see sh), from the -c option or from the system() and popen() functions defined in the System Interfaces volume of IEEE Std 1003.1-2001. If the first line of a file of shell commands starts with the characters "#!", the results are unspecified.

    The shell breaks the input into tokens: words and operators; see Token Recognition.
	* Token recognition : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03

    The shell parses the input into simple commands (see Simple Commands) and compound commands (see Compound Commands).
	* Simple commands : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_09_01	
	* Compound commands : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_09_04

    The shell performs various expansions (separately) on different parts of each command, resulting in a list of pathnames and fields to be treated as a command and arguments; see Word Expansions.
	* Word expansions : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_06

    The shell performs redirection (see Redirection) and removes redirection operators and their operands from the parameter list.
	* Redirections : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07

    The shell executes a function (see Function Definition Command), built-in (see Special Built-In Utilities), executable file, or script, giving the names of the arguments as positional parameters numbered 1 to n, and the name of the command (or in the case of a function within a script, the name of the script) as the positional parameter numbered 0 (see Command Search and Execution).

	* Function definition command : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_09_05
	* Special built-in utilitiues : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_14

    The shell optionally waits for the command to complete and collects the exit status (see Exit Status for Commands).
	* Exit status : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_08_02

*/

//__________________________________________________________________________________________________________________________________________
// Pipes

// Handle environment variables

// Handle $?

// Handle 'Ctrl+' functionnalities (signals)

// Builtin


#endif
