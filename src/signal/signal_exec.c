/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:08:21 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/13 14:08:24 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal_exec(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	signal(SIGPIPE, SIG_IGN);
}

void	signal_handler_exec(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		get_status(130);
	}
	else if (signal == SIGQUIT)
	{
		ft_printf_fd(STDERR_FILENO, "quit (core dump)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		get_status(131);
	}
}

void	signal_exec(int pid)
{
	if (pid == 0)
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
