/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:17:05 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/20 13:07:54 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_status(130);
		g_signal = 0;
	}
	else if (signal == SIGQUIT)
	{
		ft_printf_fd(STDERR_FILENO, "quit (core dump)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_status(131);
	}
}
/*
void	signal_main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
*/

void	ctrld(int fd_heredoc, t_token *token_node, int std_in)
{
	if (g_signal == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		close(fd_heredoc);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO,
			"warning: here-document delimited by end-of-file (wanted `%s')\n",
			token_node->next->content);
		close(fd_heredoc);
		get_status(0);
		return ;
	}
}

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
