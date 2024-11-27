
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
	t_minishell	*mini;
	t_termios	terminal;
	int			fd_bckp;
	int			the_end;

	the_end = 0;
	fd_bckp = dup(STDIN_FILENO);
	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (mini == NULL)
	{
		printf("Malloc fail.\n");
		return (0);
	}	
	copy_env();
	tcgetattr(STDIN_FILENO, &terminal);
	while (1)
	{
		init_signal();
		init_struct(mini);
		dup2(fd_bckp, STDIN_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
		the_end = shellzito_on(mini);
		// if(//sinal)
		// {
		// 	rl_clear_history();
		// 	close_fds(fd_bckp);
		// 	//free path env
		// 	exit(the_end);
		// }
	}
	//clear_and_free(mini);
	//free(mini->input);
	close_fds(fd_bckp);
	return (the_end);
}	
int	shellzito_on(t_minishell *mini)
{		
		if (mini->input != NULL)
        {
            free(mini->input);
            mini->input = NULL;
        }
		mini->input = readline("shellzito: ");
		add_history(mini->input);
		if (mini->input == NULL)
		{
			clear_and_free(mini);
			return (0);
		}
		validate_input(mini);
		token_type(mini->input, &(mini)->tokenlist);
		list_printer(mini->tokenlist); //apagar
		check_syntax(&(mini->tokenlist));
		search_heredoc (&(mini->tokenlist));
		across_the_universe(&(mini->tokenlist));
		all_together(&(mini->tokenlist));
		clear_list(&(mini->tokenlist));
		list_printer(mini->tokenlist); //apagar
		mini->tree = ast_builder(NULL, mini->tokenlist); //free tokenlis
		print_tree(mini->tree, 1); //apagar
		execution(mini->tree);
		free(mini->input);

	//free(mini->input); //free???
	return (get_status(-1));
}


void	close_fds(int fd_bckp)
{
	close(fd_bckp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	init_struct(t_minishell *mini)
{
	mini->input = NULL;
	mini->tokenlist = NULL;
	mini->tree = NULL;
	mini->export_list = NULL;
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
