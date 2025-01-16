/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:22 by anacaro5          #+#    #+#             */
/*   Updated: 2025/01/16 16:31:36 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_others(t_ast *node, t_minishell *mini)
{
	int		status;

	status = 0;
	node->first_cmd = ft_strdup(node->cmd_args[0]);
	if (node->first_cmd == NULL || ft_strlen(node->first_cmd) == 0)
		return (get_status(0));
	validate_cmd(node->first_cmd);
	node->path_array = split_path();
	if (node->path_array == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "shellzito: command not found\n");
		return (get_status(127));
	}
	node->exec_ready = ft_strdup(node->first_cmd);
	find_executable(node);
	status = execute_cmd(mini, node);
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
			node->exec_ready = ft_strdup(path);
			free(path);
			return (0);
		}
		free(path);
		i++;
	}
	return (-1);
}

int	execute_cmd(t_minishell *mini, t_ast *node)
{
	pid_t	pid;
	int		status;

	status = 0;
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
			bye_bye_shell(mini, status);
		}
	}
	waitpid(pid, &status, 0);
	wise_status(status);
	return (get_status(-1));
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
	path_array = NULL;
	path = get_path_env("PATH");
	if (path == NULL)
		return (path_array);
	path_array = ft_split(path, ':');
	free(path);
	return (path_array);
}
