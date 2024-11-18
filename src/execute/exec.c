/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:09:18 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/18 15:23:55 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_ast *node)
{
	if (node->type == PIPE)
		execute_pipe(node);
	if (is_redirect(node->type) == 1)
		execute_redirect(node);
	else
	{
		if (is_builtin(node->content) == 1)
			//printf("isbuiltin working\n");
			execute_builtin (node->content);  //call_builtins
		else
			execute_others (node);
	}
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

int status_shellzito(int exit_status)
{
	static int	status;

	if (exit_status != -1)
		status = exit_status;
	return (status);
}



