/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:17:05 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/21 18:58:40 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGPIPE, SIG_IGN);
} //colocar no heredoc tbm

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//get_status(130);
	}
	else if (signal == SIGQUIT)
	{
		printf("Quit (core dump)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//get_status(131);
	}
}

// void	signal_exec(void)
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// 	//signal(SIGPIPE, SIG_IGN);
// }

void	ctrld(char *input, int fd_heredoc, t_token *token_node)
{
	if (input == NULL)
	{
		printf("shellzito: warning: here-document delimited by end-of-file (wanted `%s')\n", token_node->next->content);
		close(fd_heredoc);
		//get_status(0);
		return ;
	}
}

// void	init_signal_heredoc(int fd_heredoc)
// {
	
// 		//close(fd_heredoc);
// 	signal(SIGINT, signal_handler_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// 	//signal(SIGPIPE, SIG_IGN);
// } //colocar no heredoc tbm

void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//get_status(130);
	}
}
// lembrar ctrlD na execução (NULL);

// void	signal_execution(int pid)
// {
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGPIPE, signal_readline_in_execution);
// 	}
// 	else
// 	{
// 		signal(SIGINT, signal_readline_in_execution);
// 		signal(SIGQUIT, signal_readline_in_execution);
// 		signal(SIGPIPE, SIG_IGN);
// 	}
// }
