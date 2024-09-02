
#include "../include/minishell.h"

// void	get_token(char *input)
// {
// 	char		**cmd;
// 	t_token		*token;
// 	int			i;

// 	i = 0;
// 	while (input)
// 	{
// 		;
		
// 		token->content = cmd[i];
// 		// token = token->next
// 	}

// }


void	token_type(char *input, t_token **list)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
			i = token_d_quotes();
		else if (input[i] == '\'')
			i = token_s_quotes();
		else if (input[i] == '|' && input[i + 1] != '|')
			i = token_pipe(i, input, list);
		else if (input[i] == '<' )
			i = token_;
		else if (input[i] == '>')
			i = ;
		else if (input[i] == '')
			i = ;
		else if (input[i] == '')
			i = ;
		else if (input[i] == '')
			i = ;
							
	}

}
	// '
	// "
	// <
	// >
	// <<
	// >>
	// |
	// 	word

// o $ vai entrar em word???
// }

int	token_pipe(int idx, char *input, t_token **list)
{
	int i
	t_token	*node

	node = (t_token *) ft_calloc(1, sizeof(t_token));
	node->type = PIPE;
	node->content = input[idx];
	create_node (list, node);


	i = 0;
	while
	{
	}
	return (idx + i)
}

t_token	*create_token_node (char* input, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(input);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	free(input);
	return (new);
}

void	create_token_list(t_token **token_list, t_token *token_node)
{
	t_token	*curr;

	if (*token_list == NULL)
		*token_list = token_node;
	else
	{
		curr = *token_list;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = token_node;
		token_node->prev = curr;
	}
}

int	token pipe(int idx, t_token **list)
{
	int i

	i = 1;
	while
	{
		pipe_node = (t_)
	}
	return (idx + i)
}
