/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:57:22 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/18 14:09:45 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_others(t_ast *node)
{
	char	*cmd;
	int 	i;
	char 	*curr;

	get_cmd(node);
	validate_cmd(node->first_cmd);
	node->path_array = split_path();
	if (node->path_array == NULL)
	{
		printf("shellzito: %s: command not found\n", cmd);
		return (127);
	}
	i = 0;
	node->exec_ready = ft_strdup(node->first_cmd);
	while (node->path_array[i])
	{
		curr = ft_strjoin(node->path_array[i], node->first_cmd);
		if (access(curr, X_OK) == 0)
			node->exec_ready = curr;
		break ;
		i++;
	}
	execve(node->exec_ready, node->cmd_args, env_shellzito(NULL));
	//erros que não vao existir?
	
}

void	validate_cmd(char *cmd)
{
	if ((ft_strncmp(cmd, "./", 2) == 0) || (ft_strncmp(cmd, "../", 3) == 0))
		status_shellzito(127);
}

void	*get_cmd(t_ast *node)
{
	int		i;
	char	**cmd_array;


	cmd_array = ft_split(node->content, ' ');
	node->first_cmd = ft_strdup(cmd_array[0]);
	i = 1;
	while (cmd_array[i] != NULL)
	{
		node->cmd_args = ft_strdup(cmd_array[i]);
		i++;
	}
	return ;
}

char	**split_path(void)
{
	char	*path;
	char	**path_array;

	path = get_env("PATH");
	path_array = ft_split(path, ':');
	return (path_array);
}