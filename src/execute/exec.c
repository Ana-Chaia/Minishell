/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:09:18 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/19 15:53:52 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execution(t_ast *node, t_minishell *mini)
{
	int	status;

	//printf("status_exec:\n");
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
	get_status(status);
	return (status);
}

int	is_builtin(char *cmd)
{
	size_t	len;

	if (cmd == NULL)
		return (0);
	len = (ft_strchr(cmd, ' ') - cmd);   //vf com ana se td bem
	// if (len == 0)
	// 	return (0);
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
	//ft_printf("get_status: %d\n", status);
	if (exit_status != -1)
		status = exit_status;
	//status = mod_status(status);
	return (status);
}



