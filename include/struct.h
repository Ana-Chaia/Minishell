
#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int				position;
	int				type;
	int				status;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;


}	t_token;

typedef struct s_minishell
{
	char	*input;
	t_token	*tokenlist;

}	t_minishell;

enum e_type
{
	PIPE,
	S_QUOTES,
	D_QUOTES,
	RED_IN,
	RED_OUT,
	HEREDOC,	
	APPEND,
	WORD,
};

#endif