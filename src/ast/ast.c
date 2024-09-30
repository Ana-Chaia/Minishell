/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:05:16 by anacaro5          #+#    #+#             */
/*   Updated: 2024/09/30 09:47:15 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	token_to_ast(t_token *tokenlist)
{
	t_token	*curr;
	t_ast	*joint;

	curr = tokenlist;
	joint = NULL;
	while (curr->next)
		curr = curr->next;
	while (curr != NULL)
	{
		if (curr->type == PIPE || curr->prev == NULL)
		{
			ast_builder(joint, curr);
			return;
		}
		//if (curr->prev == NULL)
		{

		}


		curr = curr->prev;
	}

}

t_ast	*ast_builder(t_ast *ast_node, t_token *curr, int, int type)
{
	t_ast	*joint;

	joint = ast_node;
	if (joint == NULL)
		return (ast_builder(ast_new_node(curr), curr->next));
	if (curr->type == PIPE)
	{
		if (joint->left != NULL)
			ast_builder (joint->left, curr);
		else
		{
			joint->left = ast_new_node(curr);
			
			joint->left->right = ast_builder(joint->left->right, curr->next);
		}
	}
	else
		joint->right = ast_builder (joint->right, curr);
}

/* t_ast	*ast_builder(t_ast *ast_node, t_token *curr)
{
	t_ast	*joint;

	joint = ast_node;
	if (joint == NULL)
		return (ast_builder(ast_new_node(curr), curr->next));
	if (joint->type == PIPE)
		joint->left = ast_builder (joint->left, curr);
	else
		joint->right = ast_builder (joint->right, curr);

	
	retorna ast node
} */




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
	return (ast_node);
}
