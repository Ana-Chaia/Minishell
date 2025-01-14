/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:12:22 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/14 17:06:34 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_signal;

int	main(void)
{
	t_minishell	*mini;
	t_termios	terminal;
	int			fd_bckp;
	int			the_end;

	the_end = 0;
	mini = NULL;
	fd_bckp = dup(STDIN_FILENO);
	mini = init_minishell(mini);
	tcgetattr(STDIN_FILENO, &terminal);
	while (1)
	{
		if (mini == NULL)
			mini = (t_minishell *)malloc(sizeof(t_minishell));
		g_signal = 0;
		init_struct(mini);
		dup2(fd_bckp, STDIN_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
		the_end = shellzito_on(mini);
	}
	bye_bye(mini);
	close_fds(fd_bckp);
	return (the_end);
}

t_minishell	*init_minishell(t_minishell *mini)
{
	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (mini == NULL)
	{
		printf("Malloc fail.\n");
		return (0);
	}
	init_signal();
	copy_env();
	return (mini);
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
		mini->input = ft_strdup("exit");
		printf("exit\n");
	}
	token_type(mini->input, &(mini)->tokenlist);
	if (check_syntax(&(mini->tokenlist)) == 1 || validate_input(mini) == 1)
		return (get_status(2));
	search_heredoc (&(mini->tokenlist));
	across_the_universe(&(mini->tokenlist));
	all_together(&(mini->tokenlist));
	clear_list(&(mini->tokenlist));
	mini->tree = ast_builder(NULL, mini->tokenlist, 0);
	execution(mini->tree, mini);
	free_mini(mini);
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
