
#include "../include/minishell.h"

void	free_tokenlist(t_token *tokenlist)
{
	t_token	*curr;
	t_token	*next;

	curr = tokenlist;
	if (tokenlist == NULL)
		return ;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
		{
			free(curr->content);
			curr->content = NULL;
			curr->next = NULL;
			curr->prev = NULL;
		}
		if (curr->cmd_args)
			free_ptrptr(curr->cmd_args);
		free(curr);
		curr = next;
	}
}

void	free_export(t_exp *export_list)
{
	t_exp	*curr;
	t_exp	*next;

	curr = export_list;
	if (export_list == NULL)
		return ;
	while (curr)
	{
		next = curr->next;
		if (curr->name)
		{
			free(curr->name);
			curr->name = NULL;
		}
		if (curr->value)
		{
			free(curr->value);
			curr->value = NULL;
		}
		curr->next = NULL;
		curr->prev = NULL;
		free(curr);
		curr = next;
	}
}

void	free_ast(t_ast *ast_node)
{
	if (ast_node == NULL)
		return ;
	if (ast_node->left)
	{
		free_ast(ast_node->left);
	}
	if (ast_node->right)
	{
		free_ast(ast_node->right);
	}
	if (ast_node->content)
		free(ast_node->content);
	if (ast_node->first_cmd)
		free(ast_node->first_cmd);
	if (ast_node->exec_ready)
		free(ast_node->exec_ready);
	if (ast_node->path_array)
		free_ptrptr(ast_node->path_array);
	free(ast_node);
	ast_node = NULL;
}

void	free_mini(t_minishell *mini)
{
	if (mini->input)
		free(mini->input);
	if (mini->tree)
	{
		free_ast(mini->tree);
	}
	if (mini->export_list)
	{
		free_export(mini->export_list);
		mini->export_list = NULL;
	}
	if (mini->tokenlist)
	{
		free_tokenlist(mini->tokenlist);
		mini->tokenlist = NULL;
	}
}
