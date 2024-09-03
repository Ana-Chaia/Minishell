
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
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] != '|')
			i = create_list (list, create_node (input, PIPE), i, 1);
		else if (input[i] == '\'')
			i = create_list (list, create_node (input, S_QUOTES), i, 1);
		else if (input[i] == '"')
			i = create_list (list, create_node (input, D_QUOTES), i, 1);
		else if (input[i] == '<' )
			i = create_list (list, create_node (input, RED_IN), i, 1);
		else if (input[i] == '>')
			i = create_list (list, create_node (input, RED_OUT), i, 1);
		else if (input[i] == '<' && input[i + 1] == '<')
			i = create_list (list, create_node (input, HEREDOC), i, 2);
		else if (input[i] == '>' && input[i + 1] == '>')
			i = create_list (list, create_node (input, APPEND), i, 2);
		else
		{
			i = token_word(list, i, input);
			printf("i: %d\n", i);
		}
	}
}

t_token	*create_node(char *input, int type)
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

int	create_list(t_token **token_list, t_token *token_node, int idx, int flag)
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
	return (idx + flag);
}

int	token_word(t_token **token_list, int idx, char *input)
{
	size_t	start;
	size_t	end;
	int		i;

	i = 0;
	if (is_space(input[idx]))
		return (idx + 1);
	start = (size_t)idx;
	idx++;
	while (input[idx] && !is_space(input[idx]) && input[idx] != '|'
		&& input[idx] != '\'' && input[idx] != '"' && input[idx] != '<'
		&& input[idx] != '>' && input[idx] != '(' && input[idx] != ')')
		idx++;
	end = (size_t)idx;
	create_list(token_list, (create_node (input, WORD)), start, (end - start));
	return (end);
}

int	is_space(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\n') || (c == '\r'))
		return (1);
	else
		return (0);
}
