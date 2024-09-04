
#include "../include/minishell.h"

int	main(void)
{
	// char		**cmd;
	t_minishell	*mini;

	// mini = NULL;
	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (mini == NULL)
	{
		printf("Malloc fail.\n");
		return (1);
	}
	init_struct(mini);
	while (1)
	{
		mini->input = readline("shellzito: ");
		printf("%s\n", mini->input);
		add_history(mini->input);
		if (mini->input == NULL)
			clear_and_free(mini);
		validate_input(mini);
		token_type(mini->input, &mini->tokenlist);
		list_printer(mini->tokenlist);
		// execve("/usr/bin/ls", args, NULL);
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

