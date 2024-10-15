
#include "../include/minishell.h"


void    print_tree(t_ast *root, int nivel)
{
    int    i;

    if (root)
    {
        print_tree(root->right, nivel + 1);
        printf("\n\n");
        for(i = 0; i < nivel; i++)
            printf("\t");
        printf("%s - %d", root->content, root->type);
        print_tree(root->left, nivel + 1);
		printf("\n\n");
    }
}


int	main(void)
{
	// char		**cmd;
	t_minishell	*mini;
	t_ast*		tree;
	t_token		*united;

	// mini = NULL;
	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (mini == NULL)
	{
		printf("Malloc fail.\n");
		return (1);
	}
	while (1)
	{
		init_struct(mini);
		mini->input = readline("shellzito: ");
		printf("%s\n", mini->input);
		add_history(mini->input);
		if (mini->input == NULL)
			clear_and_free(mini);
		validate_input(mini);
		token_type(mini->input, &mini->tokenlist);
		list_printer(mini->tokenlist);
		check_syntax(&(mini->tokenlist));
		search_heredoc (&(mini->tokenlist));
		united = all_together(&(mini->tokenlist));
		list_printer(mini->tokenlist);
		tree = ast_builder(NULL, mini->tokenlist);
		//printf("----------primeiro joint: %s\n", tree->content);
		//printf("----------1 joint esquerda : %s\n", tree->left->content);
		//printf("----------1 joint direita: %s\n", tree->right->content);
		//printf("----------direita do 1 joint à esquerda: %s\n", tree->left->right->content);
		//printf("----------esquerda do 1 joint à esquerda: %s\n", tree->left->left->content);
		//printf("----------direita do 1 joint à direita: %s\n", tree->right->right->content);
		//printf("----------esquerda do 1 joint à direita: %s\n", tree->right->left->content);
		print_tree(tree, 1);
		//ft_tree_printer(tree);
		// execve("/usr/bin/ls", args, NULL);
		//free_tokenlist(mini->tokenlist);
		
	}
	free(mini->input);
	return (0);
}

void	init_struct(t_minishell *mini)
{
	mini->input = NULL;
	mini->tokenlist = NULL;
}
// 	*tokenlist = NULL;
// 	(*tokenlist)->position = 0;
// 	(*tokenlist)->content = NULL;
// 	(*tokenlist)->type = 0;
// 	(*tokenlist)->prev = NULL;
// 	(*tokenlist)->next = NULL;
// }

void	clear_and_free(t_minishell *mini)
{
	rl_clear_history();
	printf("exit\n");
	if (mini->input)
		free(mini->input);
	free(mini);
	return ;
}

void	free_tokenlist(t_token *tokenlist)
{
	t_token	*curr;
	t_token	*next;

	curr = tokenlist;
	while (curr)
	{
		next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
	tokenlist = NULL;
}
