/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:49:07 by anacaro5          #+#    #+#             */
/*   Updated: 2025/01/14 16:58:57 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*pipe_to_ast(t_token *tokenlist)
{
	t_token	*curr;

	curr = tokenlist;
	while (curr->next)
		curr = curr->next;
	while (curr != NULL)
	{
		if ((curr->type == PIPE || curr->prev == NULL) && curr->blob == 0)
		{
			return (curr);
		}
		curr = curr->prev;
	}
	return (tokenlist);
}

t_token	*redir_to_ast(t_token *tokenlist)
{
	t_token	*curr;

	curr = tokenlist;
	while (curr->next != NULL)
	{
		if (curr->next->type == PIPE)
		{
			if (curr->type == CMD)
			{
				curr = find_last_one (curr);
				return (curr);
			}
			if (curr->type == FILENAME && curr->blob == 42)
			{
				curr = find_last_one (tokenlist);
				return (curr);
			}
			return (tokenlist);
		}
		if (is_redirect(curr->type) == 1 && curr->blob == 0)
			return (curr);
		curr = curr->next;
	}
	curr = find_last_one (tokenlist);
	return (curr);
}

t_token	*find_last_one(t_token *tokenlist)
{
	int		last_one;
	t_token	*curr;

	last_one = check_last_one(tokenlist, &curr);
	if (last_one == 1)
	{
		while (curr->next != NULL
			|| (curr->next != NULL && curr->next->type != PIPE))
		{
			if (curr->blob == 0)
				return (curr);
			curr = curr->next;
		}
	}
	return (tokenlist);
}

int	check_last_one(t_token	*tokenlist, t_token	**curr_ptr)
{
	int		last_one;
	t_token	*curr;

	last_one = 0;
	curr = tokenlist;
	if (curr->next != NULL && curr->next->type != PIPE)
	{
		while (curr->next != NULL)
		{
			curr = curr->next;
			if (curr != NULL && curr->type != PIPE)
				break ;
		}
	}
	while (curr->prev != NULL)
	{
		if (curr->blob == 0)
			last_one++;
		curr = curr->prev;
		if (curr != NULL && curr->type == PIPE)
			break ;
	}
	*curr_ptr = curr;
	return (last_one);
}

t_ast	*ast_new_node(t_token *token_node)
{
	t_ast	*ast_node;

	ast_node = (t_ast *) malloc(sizeof(t_ast));
	if (!ast_node)
		return (NULL);
	ast_node->type = token_node->type;
	ast_node->content = ft_strdup(token_node->content);
	ast_node->left = NULL;
	ast_node->right = NULL;
	ast_node->first_cmd = NULL;
	ast_node->exec_ready = NULL;
	ast_node->path_array = NULL;
	ast_node->cmd_args = token_node->cmd_args;
	return (ast_node);
}
