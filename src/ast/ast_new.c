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
		ast_builder(ast_new_node(curr), curr->next);
	if (curr->type == PIPE)
	{
		if (joint->left != NULL)
			ast_builder (joint->left, curr);
		else
		{
			if (curr->next->type == WORD)
				joint_command (joint->left, curr);
			else if (is_redirect(curr->next) == 1)
				joint_redirect (joint->left, curr);
			
// 			joint->left->right = ast_builder(joint->left->right, curr->next);
// 		}
// 	}
// 	else
		
// 		joint->right = ast_builder (joint->right, curr);
// }

t_ast	*joint_command(t_ast *ast_node, t_token *curr)
{
	t_ast	*joint;

	joint = ast_node;
	if (joint == NULL)
		joint_command(ast_new_node(curr), curr->next));
	if (is_redirect(joint->type) == 1)
		joint->left = joint_redirect (joint->left, curr);
	else
		// joint->right = ast_builder (joint->right, curr);

	
	retorna ast node
} 

t_ast	*joint_redirect(t_ast *ast_node, t_token *curr)
{
	t_ast	*joint;

	joint = ast_node;
	if (joint == NULL)
		joint_command(ast_new_node(curr), curr->next));
	if (is_redirect(joint->type) == 1)
		joint->left = joint_command (joint->left, curr);
	else
		joint->right = ast_builder (joint->right, curr);

	
	retorna ast node
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
	return (ast_node);
}


int	is_redirect(t_token	*curr)
{
	if (curr->type == RED_IN || curr->type == RED_OUT
		|| curr->type == HEREDOC || curr->type == APPEND)
		return (1);
	return (0);
}
