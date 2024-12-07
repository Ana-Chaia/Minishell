/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:49:07 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/07 14:58:20 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*pipe_to_ast(t_token *tokenlist)
{
	t_token	*curr;
//	t_ast	*joint;

	curr = tokenlist;
//	joint = NULL;
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
//	t_ast	*joint;

	curr = tokenlist;
//	joint = NULL;
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
		{
			return (curr);
		}
		curr = curr->next;
	}
	curr = find_last_one (tokenlist);
	return (curr);
}

t_token *find_last_one (t_token *tokenlist)
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
	if (last_one == 1)
	{
		while (curr->next != NULL || (curr->next != NULL && curr->next->type != PIPE))
		{
			if (curr->blob == 0)
				return (curr);
			curr = curr->next;
		}
	}
	return (tokenlist);
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
//	ast_node->parent = NULL;
	// ast_node->child = NULL;
	ast_node->first_cmd = NULL;
    ast_node->exec_ready = NULL;
    ast_node->cmd_args = NULL;
    ast_node->path_array = NULL;
	return (ast_node);
}

int	is_redirect(int curr)
{
	if (curr == RED_IN || curr == RED_OUT
		|| curr == HEREDOC || curr == APPEND)
		return (1);
	return (0);
}

t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist, int level)
{
	t_ast	*joint;
	t_token	*curr;
	t_token	*redir;

	joint = NULL;
	if (tokenlist == NULL)
		return (ast_node);
	curr = pipe_to_ast(tokenlist);  // pega o último(primeiro) pipe E o primeiro CMD
	if (curr->type != PIPE)
		curr = redir_to_ast(curr); // se curr não é PIPE, pega o primeiro redir
	if (curr == NULL)
		return (ast_node);
	if (ast_node == NULL && curr->blob != 42)
	{
		curr->blob = 42;
		joint = ast_new_node(curr);
		printf("----------level %d\tnovo joint: %s\n",level, joint->content);
	}
	else
		joint = ast_node;
	if (curr->type == PIPE)
	{
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
	else if (is_redirect(curr->type) == 1)
	{
		if (curr->next && curr->next->type == FILENAME && curr->next->blob != 42)  //faz o filename na direita
		{
			joint->right = ast_new_node(curr->next);
			curr->next->blob = 42;
			printf("----------level %d\tnovo joint_filename: %s\n",level, joint->right->content);
		}
		if (curr->prev && curr->prev->type != PIPE)     //faz o cmd na esquerda 
			joint->left = ast_builder(joint->left, curr->prev, level + 1);
		if (curr->next->next && curr->next->next->type != PIPE)
			joint->left = ast_builder(joint->left, curr->next->next, level + 1);
	}
	else if (curr->prev == NULL && curr->blob == 0)
	{
		curr->blob = 42;
		redir = redir_to_ast(curr);                  // faz o primeiro redir na esquerda
		if (redir != curr)
			joint->left = ast_builder(joint->left, redir, level + 1);
		joint->left = ast_builder(joint->left, curr, level + 1);
	}
	return (joint);
}

