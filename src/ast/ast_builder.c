/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:01:54 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/19 12:08:42 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(int curr)
{
	if (curr == RED_IN || curr == RED_OUT
		|| curr == HEREDOC || curr == APPEND)
		return (1);
	return (0);
}

void	handle_pipe(t_ast *joint, t_token *curr, int level)
{
	t_token	*redir;

	if (joint->left == NULL)
		joint->left = ast_builder(joint->left, curr, level + 1);
	if (curr->next)
	{
		redir = redir_to_ast(curr->next);
		if (redir != curr->next)
			joint->right = ast_builder(joint->right, redir, level + 1);
		if (curr->next && curr->next->type == CMD)
			joint->right = ast_builder(joint->right, curr->next, level + 1);
	}
}

void	handle_redirect(t_ast *joint, t_token *curr, int level)
{
	if (curr->next && curr->next->type == FILENAME && curr->next->blob != 42)
	{
		joint->right = ast_new_node(curr->next);
		curr->next->blob = 42;
	}
	if (curr->prev && curr->prev->type != PIPE)
		joint->left = ast_builder(joint->left, curr->prev, level + 1);
	if (curr->next->next && curr->next->next->type != PIPE)
		joint->left = ast_builder(joint->left, curr->next->next, level + 1);
}

void	handle_special_case(t_ast *joint, t_token *curr, int level)
{
	t_token	*redir;

	curr->blob = 42;
	redir = redir_to_ast(curr);
	if (redir != curr)
		joint->left = ast_builder(joint->left, redir, level + 1);
	joint->left = ast_builder(joint->left, curr, level + 1);
}

t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist, int level)
{
	t_ast	*joint;
	t_token	*curr;

	if (tokenlist == NULL)
		return (ast_node);
	curr = pipe_to_ast(tokenlist);
	if (curr->type != PIPE)
		curr = redir_to_ast(curr);
	if (curr == NULL)
		return (ast_node);
	if (ast_node == NULL && curr->blob != 42)
	{
		curr->blob = 42;
		joint = ast_new_node(curr);
	}
	else
		joint = ast_node;
	if (curr->type == PIPE)
		handle_pipe(joint, curr, level);
	else if (is_redirect(curr->type) == 1)
		handle_redirect(joint, curr, level);
	else if (curr->prev == NULL && curr->blob == 0)
		handle_special_case(joint, curr, level);
	return (joint);
}
