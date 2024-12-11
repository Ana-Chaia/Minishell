/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:58:21 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/10 12:39:57 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	token_type(char *input, t_token **list)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] != '|')
			i = make_lst (list, create_node (&input[i], PIPE, 0, 1), i, 1);
		else if (input[i] == '\'')
			i = token_s_quotes(list, i, input);
		else if (input[i] == '"')
			i = token_d_quotes(list, i, input);
		else if (input[i] == '<' && input[i + 1] != '<')
			i = make_lst (list, create_node (&input[i], RED_IN, 0, 1), i, 1);
		else if (input[i] == '>' && input[i + 1] != '>')
			i = make_lst (list, create_node (&input[i], RED_OUT, 0, 1), i, 1);
		else if (input[i] == '<' && input[i + 1] == '<')
			i = make_lst (list, create_node (&input[i], HEREDOC, 0, 2), i, 2);
		else if (input[i] == '>' && input[i + 1] == '>')
			i = make_lst (list, create_node (&input[i], APPEND, 0, 2), i, 2);
		else
			i = token_word(list, i, input);
	}

}

t_token	*create_node(char *input, int type, int idx, int flag)
{
	t_token	*new;
	char	*substr;
	int		x;

	x = 0;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	substr = ft_substr(input, idx, flag);
	new->content = ft_strdup(substr);
	free(substr);
	new->type = type;
	new->blob = x;
	new->quote_issue = 0;
	new->next = NULL;
	new->prev = NULL;
	//if (type == S_QUOTES || type == D_QUOTES)
	//	new->quote = 42;
	//else
	//	new->quote = 0;
	return (new);
}

int	make_lst(t_token **token_list, t_token *token_node, int idx, int flag)
{
	t_token	*curr;

	curr = NULL;
	if (*token_list == NULL)
	{
		*token_list = token_node;
		token_node->position = 1;
	}
	else
	{
		curr = *token_list;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = token_node;
		token_node->prev = curr;
		token_node->position = curr->position + 1;
	}
	return (idx + flag);
}

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
	validate_quote_issue (token_list, start, end, input);
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
	validate_quote_issue (token_list, start, end, input);
	return (end);
}

void validate_quote_issue (t_token **token_list, size_t start,
	size_t end,	char *input)
{
	t_token	*curr;

	curr = *token_list;
	while (curr->next != NULL)
		curr = curr->next;
	if (input[start - 1] && (is_space (input[start - 1]) == 0))
		curr->quote_issue = 1;
	if (input[end] && (is_space (input[end]) == 0))
		curr->quote_issue = 2;
}


int	token_word(t_token **token_list, int idx, char *input)
{
	size_t	start;
	size_t	end;

	if (is_space(input[idx]))
		return (idx + 1);
	start = (size_t)idx;
	idx++;
	while (input[idx] && !is_space(input[idx]) && input[idx] != '|'
		&& input[idx] != '\'' && input[idx] != '"' && input[idx] != '<'
		&& input[idx] != '>')
		idx++;
	end = (size_t)idx;
	make_lst(token_list, (create_node (input, WORD, start, end - start)),
		start, (end - start));
	return (end);
}


int	is_space(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\n') || (c == '\r'))
		return (1);
	else
		return (0);
}
