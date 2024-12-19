/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:17:05 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/19 15:31:32 by jbolanho         ###   ########.fr       */
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
	g_signal = signal;
	if (signal == SIGINT)
	{
		//write(1, "\n", 1);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line(); 
		rl_replace_line("", 0);
		rl_redisplay();
		get_status(130);
	}
	else if (signal == SIGQUIT)
	{
		ft_printf_fd(STDERR_FILENO, "quit (core dump)\n");
		//printf("Quit (core dump)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_status(131);
	}
}

void	signal_main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGPIPE, SIG_IGN);
}

void	ctrld(int fd_heredoc, t_token *token_node, int std_in)
{
	if (g_signal == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		//printf("FECHOU ĉ");   //apagar
		// if(hd_input)
		// // {
		// // 	free(hd_input);
		// // 	hd_input = NULL;
		// // }
		close(fd_heredoc);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "warning: here-document delimited by end-of-file (wanted `%s')\n", token_node->next->content);
		//("shellzito: warning: here-document delimited by end-of-file (wanted `%s')\n", token_node->next->content);
		close(fd_heredoc);
		get_status(0);
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
	g_signal = signal;
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_status(130);
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


void	init_signal_exec(void)
{
	//printf("SINAL NA EXECUCAO\n");   //apagar
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	signal(SIGPIPE, SIG_IGN);
} //colocar no heredoc tbm

void	signal_handler_exec(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
		get_status(130);
	}
	else if (signal == SIGQUIT)
	{
		ft_printf_fd(STDERR_FILENO, "quit (core dump)\n");
		//printf("Quit (core dump)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	//	rl_redisplay();
		get_status(131);
	}
}

void	signal_exec(int pid)
{
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, signal_handler_exec);
	}
	else
	{
		signal(SIGINT, signal_handler_exec);
		signal(SIGQUIT, signal_handler_exec);
		signal(SIGPIPE, SIG_IGN);
	}
}