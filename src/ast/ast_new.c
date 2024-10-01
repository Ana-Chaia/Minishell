/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:49:07 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/01 12:07:43 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_to_ast(t_token *tokenlist)
{
	t_token	*curr;
	t_ast	*joint;

	curr = tokenlist;
	joint = NULL;
	while (curr->next)
		curr = curr->next;
	while (curr != NULL)
	{
		if ((curr->type == PIPE || is_redirect(curr) == 1 || curr->prev == NULL) && curr->status == 0)
		{
			//curr->status = 42;
			return (curr);
		}
		curr = curr->prev;
	}
	return (NULL);
}

t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist)
{
	t_ast	*joint;
	t_token	*curr;

	if (tokenlist == NULL)
		return (ast_node);
	curr = token_to_ast(tokenlist);
	if (curr == NULL)
		return (ast_node);
	if (ast_node == NULL)
		joint = ast_new_node(curr);
	else
		joint = ast_node;
	if (curr->type == PIPE)
	{
		if (joint->left == NULL)
			joint->left = ast_builder(joint->left, curr);
		if (tokenlist->next->type == WORD)
			joint->right = ast_builder(joint->right, curr);
		else
			joint->right = ast_builder(joint->left, curr);
	}
	else if (is_redirect(curr) == 1)
	{
		if (curr->next->type == WORD)
			joint->right = ast_builder(joint->right, curr);
		else
			joint->left = ast_builder(joint->left, curr);
	}
	else
	{
		joint->left = ast_builder(joint->left, curr);
	}
	return (joint);
}

t_ast	*ast_new_node(t_token *token_node)
{
	t_ast	*ast_node;

	ast_node = (t_ast *) malloc(sizeof(t_ast));
	if (!ast_node)
		return (NULL);
	ast_node->type = token_node->type;
	ast_node->content = token_node->content;
	ast_node->left = NULL;
	ast_node->right = NULL;
	ast_node->parent = NULL;
	ast_node->child = NULL;
	return (ast_node);
}


int	is_redirect(t_token	*curr)
{
	if (curr->type == RED_IN || curr->type == RED_OUT
		|| curr->type == HEREDOC || curr->type == APPEND)
		return (1);
	return (0);
}

// t_ast	*joint_command(t_ast *ast_node, t_token *curr)
// {
// 	t_ast	*joint;

// 	joint = ast_node;
// 	if (joint == NULL)
// 		joint_command(ast_new_node(curr), curr->next));
// 	if (is_redirect(joint->type) == 1)
// 		joint->left = joint_redirect (joint->left, curr);
// 	else
// 		// joint->right = ast_builder (joint->right, curr);

	
// 	retorna ast node
// } 

// t_ast	*joint_redirect(t_ast *ast_node, t_token *curr)
// {
// 	t_ast	*joint;

// 	joint = ast_node;
// 	if (joint == NULL)
// 		joint_command(ast_new_node(curr), curr->next));
// 	if (is_redirect(joint->type) == 1)
// 		joint->left = joint_command (joint->left, curr);
// 	else
// 		joint->right = ast_builder (joint->right, curr);

	
// 	retorna ast node
// }
