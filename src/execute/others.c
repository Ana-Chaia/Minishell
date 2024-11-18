/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:22 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/18 16:44:38 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_others(t_ast *node)
{
	//char	*cmd;
	int 	i;
	char 	*curr;
	int		pid;
	char	*path;

	get_cmd(node);
	validate_cmd(node->first_cmd);
	node->path_array = split_path();
	if (node->path_array == NULL)
	{
		printf("shellzito: %s: command not found\n", node->first_cmd);
		return (127);
	}
	i = 0;
	node->exec_ready = ft_strdup(node->first_cmd);
	while (node->path_array[i])
	{
		curr = ft_strjoin(node->path_array[i], "/");
		path = ft_strjoin(curr, node->first_cmd);
		printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			node->exec_ready = path;
			break ;
		}	
		i++;
	}
	printf("exec_ready: %s\n", node->exec_ready);
	pid = fork();
	if (pid == -1)
	{
		printf("pipe error \n");
		return (-1);		
	}
	printf("pid: %d\n", pid);
	signal_exec(pid);
	if (pid == 0)
	{
		printf("teste execve1");
		execve(node->exec_ready, node->cmd_args, env_shellzito(NULL));
		printf("teste execve");
	//erros que não vao existir?
	}
	return (0);
}

void	validate_cmd(char *cmd)
{
	if ((ft_strncmp(cmd, "./", 2) == 0) || (ft_strncmp(cmd, "../", 3) == 0))
		status_shellzito(127);
}

void	get_cmd(t_ast *node)
{
	int		i;
	int		j;
	char	**cmd_array;
	size_t	size;

	size = 0;
	node->cmd_args = NULL;
	cmd_array = ft_split(node->content, ' ');
	node->first_cmd = ft_strdup(cmd_array[0]);
	i = 1;
	j = 0;
	while (cmd_array[size] != NULL)
		size++;
	node->cmd_args = malloc((size + 1) * sizeof(char *));
	while (cmd_array[i] != NULL)
	{
		node->cmd_args[j] = ft_strdup(cmd_array[i]);
		i++;
		j++;
	}
	return ;
}

char	**split_path(void)
{
	char	*path;
	char	**path_array;
	int i = 0;

	path = getenv("PATH");
	path_array = ft_split(path, ':');
	while( path_array[i])
	{
		printf("path[%d]: %s\n", i, path_array[i]);
		i++;
	}	
	return (path_array);
}