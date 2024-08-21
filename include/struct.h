
#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;

}	t_token;

typedef struct s_minishell
{
	char	*input;
	t_token	*token;

}	t_minishell;

#endif