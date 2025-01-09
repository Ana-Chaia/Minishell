
#include "../include/minishell.h"

int	token_d_quotes(t_token **token_list, int idx, char *input)
{
	size_t	start;
	size_t	end;

	start = (size_t)idx;
	idx++;
	while (input[idx] && input[idx] != '"')
		idx++;
	end = (size_t)idx + 1;
	make_lst(token_list, (create_node (input, D_QUOTES, start, end - start)),
		start, (end - start));
	valid_quote (token_list, start, end, input);
	return (end);
}

int	token_s_quotes(t_token **token_list, int idx, char *input)
{
	size_t	start;
	size_t	end;

	start = (size_t)idx;
	idx++;
	while (input[idx] && input[idx] != '\'')
		idx++;
	end = (size_t)idx + 1;
	make_lst(token_list, (create_node (input, S_QUOTES, start, end - start)),
		start, (end - start));
	valid_quote (token_list, start, end, input);
	return (end);
}

void	valid_quote(t_token **token_list, size_t start, size_t end, char *input)
{
	t_token	*curr;

	curr = *token_list;
	while (curr->next != NULL)
		curr = curr->next;
	if (input[start - 1] && (is_space (input[start - 1]) == 0))
		curr->quote_issue_prev = 1;
	if (input[end] && (is_space (input[end]) == 0))
		curr->quote_issue_next = 1;
}
