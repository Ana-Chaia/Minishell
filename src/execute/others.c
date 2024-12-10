/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:22 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/10 13:58:20 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_others(t_ast *node)
{
	//char	*cmd;
	int 	i;
	char 	*curr;
	pid_t	pid;
	char	*path;
	//char	**env;
	int		status;

	status = 0;
	get_cmd(node);
	validate_cmd(node->first_cmd);
	node->path_array = split_path();
	if (node->path_array == NULL)
	{
		printf("shellzito: %s: command not found\n", node->first_cmd);
		return (get_status(127));
	}
	i = 0;
	node->exec_ready = ft_strdup(node->first_cmd);
	while (node->path_array[i])
	{
		curr = ft_strjoin(node->path_array[i], "/");
		path = ft_strjoin(curr, node->first_cmd);
		free(curr);
		printf("path = %s\n", path);
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
	printf("exec_ready: %s\n", node->exec_ready);
	printf("first_cmd: %s\n", node->first_cmd);
	while (node->cmd_args[i])
	{
		printf("cmd_args[%d]: %s\n", i, node->cmd_args[i]);
		i++;
	}
	i = 0;
	//env = env_shellzito(NULL);
	pid = fork();
	if (pid == -1)
	{
		perror("Pipe error \n");
		return (get_status(-1));		
	}
	printf("pid: %d\n", pid);
	signal_exec(pid);
	if (pid == 0)
	{
		printf("pid dentro do if: %d\n", pid);
		if (execve(node->exec_ready, node->cmd_args, env_shellzito(NULL)))
			status = gone_wrong(node);
			//free em MINI??
	}
	waitpid(pid, &status, 0);
	wise_status(status);
	return (WEXITSTATUS(status));
}

void	validate_cmd(char *cmd)
{
	if ((ft_strncmp(cmd, "./", 2) == 0) || (ft_strncmp(cmd, "../", 3) == 0))
		get_status(127);
}

void	get_cmd(t_ast *node)
{
	int		i;
	char	**cmd_array;
	size_t	size;

	size = 0;
	node->cmd_args = NULL;
	cmd_array = ft_split(node->content, ' ');
	node->first_cmd = ft_strdup(cmd_array[0]);
	i = 0;
	while (cmd_array[size] != NULL)
		size++;
	node->cmd_args = malloc((size + 1) * sizeof(char *));
	while (cmd_array[i] != NULL)
	{
		node->cmd_args[i] = ft_strdup(cmd_array[i]);
		i++;
	}
	node->cmd_args[i] = NULL;
	free_ptrptr(cmd_array);
	return ;
}

char	**split_path(void)
{
	char	*path;
	char	**path_array;
	int		i;

	i = 0;
	path = getenv("PATH");
	path_array = ft_split(path, ':');
	while( path_array[i])
	{
		printf("path[%d]: %s\n", i, path_array[i]);
		i++;
	}	
	return (path_array);
}
int gone_wrong(t_ast *node)
{
	int		status;

	if (ft_strcmp(node->exec_ready, node->first_cmd) == 0 && is_directory(node->exec_ready) == -1)
	{
		printf("shellzito: %s: command not found\n", node->first_cmd);
		return (get_status(127));
	}
	else if (access(node->exec_ready, F_OK) == -1)
	{
		printf("shellzito: %s: no such file or directory\n", node->first_cmd);
		return (get_status(1));
	}
	else if (is_directory(node->exec_ready) == 1)
	{
		printf("shellzito: %s: is a directory\n", node->first_cmd);
		return (get_status(126));
	}
	else if (access(node->exec_ready, X_OK) == -1
		&& access(node->exec_ready, R_OK | W_OK) == -1)
	{
		printf("shellzito: %s: permission denied\n", node->first_cmd);
		return (get_status(126));
	}
	status = get_status(-1);
	return (status);
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
		get_status(0);
}