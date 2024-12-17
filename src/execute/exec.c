/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:09:18 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/17 14:00:04 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execution(t_ast *node, t_minishell *mini)
{
	int	status;

	if (g_signal == SIGINT)
	{
		return (130);
	}
	init_signal_exec();
	if (node->type == PIPE)
		status = execute_pipe(node, mini);
	else if (is_redirect(node->type) == 1)
		status = execute_redirect(node, mini);
	else if (is_builtin(node->content) == 1)
		status = execute_builtin (node, mini);
	else
		status = execute_others (node);
	return (status);
}

int	is_builtin(char *cmd)
{
	size_t	len;

	len = (ft_strchr(cmd, ' ') - cmd);   //vf com ana se td bem
	if (len == 0)
		return (0);
	if (strncmp(cmd, "echo", len) == 0
		|| strncmp(cmd, "cd", len) == 0
		|| strncmp(cmd, "pwd", len) == 0
		|| strncmp(cmd, "export", len) == 0
		|| strncmp(cmd, "unset", len) == 0
		|| strncmp(cmd, "env", len) == 0
		|| strncmp(cmd, "exit", len) == 0)
		return (1);
	return (0);
}

int	get_status(int exit_status)
{
	static int	status;

	if (exit_status != -1)
		status = exit_status;
	return (status);
}



