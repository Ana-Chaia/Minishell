
#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int				position;
	int				type;
	int				blob;
	char			*content;
	int				quote_issue;
	int				quote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_ast
{
	//int				*type;
	int				type;
	char			*content;
	char			*first_cmd;
	char			*exec_ready;
	char			**cmd_args;
	char			**path_array;
	int				quote;
	struct s_ast	*left;
	struct s_ast	*right;
	//struct s_ast	*parent;
	// struct s_ast	*child;
}				t_ast;

typedef struct s_export
{
	char			*name;
	char			*value;
	int				on_env;
	int				equal;
	struct s_export	*next;
	struct s_export	*prev;
}	t_export;

typedef struct s_minishell
{
	char		*input;
	t_token		*tokenlist;
	t_ast		*tree;
	t_export	*export_list;
}	t_minishell;

enum e_type
{
	PIPE, //0
	S_QUOTES,
	D_QUOTES,
	RED_IN,
	RED_OUT,
	HEREDOC,	
	APPEND,
	WORD,
	FILENAME,
	CMD,
	ENDKEY,
};



#endif