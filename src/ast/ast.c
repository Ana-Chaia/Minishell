/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:49:07 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/05 13:50:47 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*pipe_to_ast(t_token *tokenlist)
{
	t_token	*curr;
	t_ast	*joint;

	curr = tokenlist;
	joint = NULL;
	while (curr->next)
		curr = curr->next;
	while (curr != NULL)
	{
		if ((curr->type == PIPE || curr->prev == NULL) && curr->blob == 0)
		{
			//curr->blob = 42;
			// printf("BlobsToken: %s, Type: %d, Blob: %d\n", curr->content, curr->type, curr->blob);
			return (curr);
		}
		// printf("Token: %s, Type: %d, Blob: %d\n", curr->content, curr->type, curr->blob);
		curr = curr->prev;
	}
	return (tokenlist);
}

t_token	*redir_to_ast(t_token *tokenlist)
{
	t_token	*curr;
	t_ast	*joint;

	curr = tokenlist;
	joint = NULL;
	// while (curr->next)
	// 	curr = curr->next;
	while (curr != NULL && curr->next != PIPE)
	{
		if (is_redirect(curr) == 1 && curr->blob == 0)
		{
			curr->blob = 42;
			printf("BlobsToken: %s, Type: %d, Blob: %d\n", curr->content, curr->type, curr->blob);
			return (curr);
		}
		printf("Token: %s, Type: %d, Blob: %d\n", curr->content, curr->type, curr->blob);
		curr = curr->next;
	}
	return (tokenlist);
}


														// t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist)
														// {
														// 	t_ast	*joint;
														// 	t_token	*curr;

														// 	if (tokenlist == NULL)
														// 		return (ast_node);
														// 	curr = token_to_ast(tokenlist);
														// 	if (curr == NULL)
														// 		return (ast_node);
														// 	if (ast_node == NULL)
														// 		joint = ast_new_node(curr);
														// 	else
														// 		joint = ast_node;
														// 	if (curr->type == PIPE)
														// 	{
														// 		if (joint->left == NULL)
														// 			joint->left = ast_builder(joint->left, curr);
														// 		if (tokenlist->next->type == WORD)
														// 			joint->right = ast_builder(joint->right, curr);
														// 		else
														// 			joint->right = ast_builder(joint->left, curr);
														// 	}
														// 	else if (is_redirect(curr) == 1)
														// 	{
														// 		if (curr->next->type == WORD)
														// 			joint->right = ast_builder(joint->right, curr);
														// 		else
														// 			joint->left = ast_builder(joint->left, curr);
														// 	}
														// 	else
														// 	{
														// 		joint->left = ast_builder(joint->left, curr);
														// 	}
														// 	return (joint);
														// }

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
	// ast_node->child = NULL;
	return (ast_node);
}

int	is_redirect(t_token	*curr)
{
	if (curr->type == RED_IN || curr->type == RED_OUT
		|| curr->type == HEREDOC || curr->type == APPEND)
		return (1);
	return (0);
}

t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist)
{
	t_ast	*joint;
	t_token	*curr;
	t_token	*redir;

	joint = NULL;
	if (tokenlist == NULL)
		return (ast_node);
	curr = pipe_to_ast(tokenlist);
	//printf("Retorno da pipe_to_ast: %p\n", curr);
	if (curr == NULL)
		{return (ast_node);}
	//printf("Tipo da pipe_to_ast: %d\n", curr->type);
	//printf("Tipo da pipe_to_ast: %s\n", curr->content);
	//if (curr->blob == 0)
	{
		if (ast_node == NULL)
		{
			curr->blob = 42;
			joint = ast_new_node(curr);
			printf("----------novo joint: %s\n", joint->content);
		}
		else
			joint = ast_node;
		if (curr->type == PIPE)
		{
			if (joint->left == NULL)
				// joint->left = ast_builder(joint->left, tokenlist)
				joint->left = ast_builder(joint->left, curr);
			if (curr->next)
			{
				redir = redir_to_ast(curr->next);
				if (redir != curr->next)
					joint->right = ast_builder(joint->right, redir);
				else if (curr->next && curr->next->type == WORD && redir == curr->next)
					joint->right = ast_builder(joint->right, curr->next->next);
		// else
		// 	joint->right = ast_builder(joint->left, curr);
		// como sai daqui??  qndo é pipe e ja colocou tudo
		// colocou em uma variável e avançou o current para sair do pipe
			}
		}
		//criar hipõtese de redir fora do pipe
		
		else if (is_redirect(curr) == 1)
		{
			if (curr->next && curr->next->type == WORD)
				joint->right = ast_builder(joint->right, curr->next);
			if (curr->prev && curr->prev->type != PIPE)
			{
			// tem mais redir?
			// redir = redir_to_ast(curr);
			// if (redir != curr)
			// 		joint->left = ast_builder(joint->left, redir);
				joint->left = ast_builder(joint->left, curr->prev);
			}
		}
		else if (curr->prev == NULL && curr->blob == 0)
		{
			curr->blob = 42;
			redir = redir_to_ast(curr);
			if (redir != curr)
				joint->left = ast_builder(joint->left, redir);
			joint->left = ast_builder(joint->left, curr);
		}
	}
	return (joint);
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

											// t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist)
											// {
											// 	t_ast	*joint;
											// 	t_token	*curr;

											// 	if (tokenlist == NULL)
											// 		return (ast_node);
											// 	curr = pipe_to_ast(tokenlist);
											// 	if (curr == NULL)
											// 		return (ast_node);
											// 	if (ast_node == NULL)
											// 		joint = ast_new_node(curr);
											// 	else
											// 		joint = ast_node;
											// 	if (curr->type == PIPE)
											// 	{
											// 		if (joint->left == NULL)
											// 			// joint->left = ast_builder(joint->left, tokenlist)
											// 			joint->left = ast_builder(joint, curr);
											// 		if (redir_to_ast(curr) != curr)
											// 			joint->right = ast_builder(joint->right, redir_to_ast(curr));
											// 		if (redir_to_ast(curr) == curr && curr->next && curr->next->type == WORD)
											// 			joint->right = ast_builder(joint->right, curr->next);
											// 		// else
											// 		// 	joint->right = ast_builder(joint->left, curr);
											// 		// como sai daqui??  qndo é pipe e ja colocou tudo
											// 	}
											// 	else if (is_redirect(curr) == 1)
											// 	{
											// 		if (curr->next->type == WORD)
											// 			joint->right = ast_builder(joint->right, curr);
											// 		else
											// 			joint->left = ast_builder(joint->left, curr);
											// 	}
											// 	else
											// 	{
											// 		joint->left = ast_builder(joint->left, curr);
											// 	}
											// 	return (joint);
											// }
