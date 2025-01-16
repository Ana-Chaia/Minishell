/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:39:11 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/15 21:33:39 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	gone_wrong(t_ast *node)
{
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
		|| access(node->exec_ready, R_OK | W_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "permission denied\n");
		return (get_status(126));
	}
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
		printf("status wise status: %d\n", status);
		status = WTERMSIG(status);
		if (status == SIGINT)
			get_status(130);
		else if (status == SIGQUIT)
		{
			signal(SIGPIPE, SIG_IGN);
			get_status(131);
		}
	}
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		get_status(status);
	}
	else
		get_status(-1);
}

char	*get_path_env(char *name)
{
	char	**env;
	int		i;
	int		j;
	char	*path;
	char	*temp;

	i = 0;
	env = env_shellzito(NULL);
	path = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j] != '\0')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (ft_strcmp(temp, name) == 0)
		{
			if (env[i][j] != '\0')
				path = substr_noquote(env[i], j + 1, ft_strlen(env[i]) - j);
		}
		free(temp);
		i++;
	}
	return (path);
}
