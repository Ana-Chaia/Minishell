
#include "../include/minishell.h"

int	main(void)
{
	// char		**args;
	t_minishell	*mini;

	mini = NULL;
	init_struct(mini);
	while (1)
	{
		mini->token = NULL;
		mini->input = readline("shellzito: ");
		printf("%s\n", mini->input);
		add_history(mini->input);
		if (mini->input == NULL)
			clear_and_free(mini);

		// args = take_token(mini->input);
		// execve("/usr/bin/ls", args, NULL);
	}
	return (0);
}

void	init_struct(t_minishell *mini)
{
	mini->input = NULL;
}

void	clear_and_free(t_minishell *mini)
{
	rl_clear_history();
	free(mini->input);
	return ;
}

