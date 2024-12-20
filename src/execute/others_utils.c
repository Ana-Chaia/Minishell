/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:39:11 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/20 14:22:36 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	gone_wrong(t_ast *node)
{
	//int		status;
	if (ft_strcmp(node->exec_ready, node->first_cmd) == 0 
		&& is_directory(node->exec_ready) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "command not found\n");
		return (get_status(127));
	}
	else if (access(node->exec_ready, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "no such file or directory\n");
		return (get_status(127));
	}
	else if (is_directory(node->exec_ready) == 1)
	{
		ft_printf_fd(STDERR_FILENO, "is a directory\n");
		return (get_status(126));
	}
	else if (access(node->exec_ready, X_OK) == -1
		&& access(node->exec_ready, R_OK | W_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "permission denied\n");
		return (get_status(126));
	}
	//status = get_status(-1);
	return (get_status(-1));
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (-1);
	return (S_ISDIR(statbuf.st_mode));
}

void	wise_status(int status)
{
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGINT)
			get_status(130);
		else if (status == SIGQUIT)
		{
			signal(SIGPIPE, SIG_IGN);
			get_status(131);
		}
	}
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		get_status(status);
	}
	else
		get_status(-1);
}
