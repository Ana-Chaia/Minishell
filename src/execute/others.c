/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:22 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/18 17:23:31 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
int	execute_others(t_ast *node)
{
	int		i;
	char	*curr;
	pid_t	pid;
	char	*path;
	int		status;

	status = 0;
	node->first_cmd = ft_strdup(node->cmd_args[0]);
	if (node->first_cmd == NULL)
		return (get_status(0));
	validate_cmd(node->first_cmd);
	node->path_array = split_path();
	if (node->path_array == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "shellzito: command not found\n");
		return (get_status(127));
	}
	i = 0;
	node->exec_ready = ft_strdup(node->first_cmd);
	while (node->path_array[i])
	{
		curr = ft_strjoin(node->path_array[i], "/");
		path = ft_strjoin(curr, node->first_cmd);
		free(curr);
		if (access(path, X_OK) == 0)
		{
			free(node->exec_ready);
			node->exec_ready = NULL;
			node->exec_ready = ft_strdup(path);
			free(path);
			break ;
		}
		free(path);
		i++;
	}
	i = 0;
	while (node->cmd_args[i])
	{
		i++;
	}
	i = 0;
	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipe error\n");
		return (get_status(-1));
	}
	signal_exec(pid);
	if (pid == 0)
	{
		if (execve(node->exec_ready, node->cmd_args, env_shellzito(NULL)))
		{
			status = gone_wrong(node);
			exit (status);
		}
	}
	waitpid(pid, &status, 0);
	wise_status(status);
	return (WEXITSTATUS(status));
} */

int	execute_others(t_ast *node)
{
	int		status;

	status = 0;
	node->first_cmd = ft_strdup(node->cmd_args[0]);
	if (node->first_cmd == NULL)
		return (get_status(0));
	validate_cmd(node->first_cmd);
	node->path_array = split_path();
	if (node->path_array == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "shellzito: command not found\n");
		return (get_status(127));
	}
	node->exec_ready = ft_strdup(node->first_cmd);
	if (find_executable(node) == -1)
		return (get_status(127));
	status = execute_cmd(node);
	return (status);
}

int	find_executable(t_ast *node)
{
	int		i;
	char	*curr;
	char	*path;

	i = 0;
	while (node->path_array[i])
	{
		curr = ft_strjoin(node->path_array[i], "/");
		path = ft_strjoin(curr, node->first_cmd);
		free(curr);
		if (access(path, X_OK) == 0)
		{
			free(node->exec_ready);
			//node->exec_ready = NULL;
			node->exec_ready = ft_strdup(path);
			free(path);
			return (0);
		}
		free(path);
		i++;
	}
	return (-1);
}

int	execute_cmd(t_ast *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipe error\n");
		return (get_status(-1));
	}
	signal_exec(pid);
	if (pid == 0)
	{
		if (execve(node->exec_ready, node->cmd_args, env_shellzito(NULL)))
		{
			status = gone_wrong(node);
			exit (status);
		}
	}
	waitpid(pid, &status, 0);
	wise_status(status);
	return (WEXITSTATUS(status));
}

void	validate_cmd(char *cmd)
{
	if (cmd == NULL)
		return ;
	if ((ft_strncmp(cmd, "./", 2) == 0) || (ft_strncmp(cmd, "../", 3) == 0))
		get_status(127);
}

char	**split_path(void)
{
	char	*path;
	char	**path_array;
	int		i;

	i = 0;
	path = getenv("PATH");
	path_array = ft_split(path, ':');
	while (path_array[i])
	{
		i++;
	}
	return (path_array);
}
