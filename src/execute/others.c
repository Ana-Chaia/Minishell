/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:22 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/04 11:50:28 by jbolanho         ###   ########.fr       */
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
	char	**env;

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
			break ;
		}	
		free(path);
		i++;
	}
	i = 0;
	printf("exec_ready: %s\n", node->exec_ready);
	while (node->cmd_args[i])
	{
		printf("cmd_args[%d]: %s\n", i, node->cmd_args[i]);
		i++;
	}
	i = 0;
	env = env_shellzito(NULL);
	// while (env[i])
	// {
	// 	printf("env[%d]: %s\n", i, env[i]);
	// 	i++;
	// }
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
		{
			perror ("shellzito ");    //apagar?????
			printf("Shellzito !!!: command not found \n");  /// apagar??
			printf("%s: command not found \n", node->first_cmd);   
			get_status(127);
			exit(127);
		}
		printf("teste execve certo");   //apagar
	}
	//erros que não vao existir?
	waitpid(pid, NULL, 0);
	if(path)
		free(path);
	if(path)
		printf("%s: PATH \n", path);
	return (0);
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
