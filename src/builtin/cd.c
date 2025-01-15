/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:19:34 by anacaro5          #+#    #+#             */
/*   Updated: 2025/01/15 12:27:46 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char **cmd)
{
	char	*old_pwd;
	char	*pwd;
	char	*path;
	char	**our_env;

	our_env = env_shellzito(NULL);
	path = NULL;
	pwd = NULL;
	if (!cmd[1])
		return (get_status(0));
	if (cmd[2])
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		get_status(1);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	path = cd_aux(cmd);
	if (chdir(path) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "cd: no such file or directory\n");
		get_status(1);
		free(path);
		free(old_pwd);
		return (1);
	}
	free(path);
	pwd = getcwd(NULL, 0);
	vars_to_env(old_pwd, pwd, our_env);
	free (old_pwd);
	free (pwd);
	return (0);
}

char	*cd_aux(char **cmd)
{
	char	*path;

	if (!cmd[1])
	{
		path = getenv("HOME");
		if (path == NULL)
			ft_printf_fd(STDERR_FILENO,
				"cd: could not get the home directory\n");
	}
	else
		path = get_path(cmd[1], NULL);
	return (path);
}

char	*get_path(char *path, char	*new)
{
	char	*x;
	size_t	len;
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	x = getcwd(NULL, 0);
	if ((path[0] == '.') && (path[1] == '\0'))
		new = ft_strdup(x);
	else if ((path[0] == '.') && (path[1] && path[1] != '.'))
	{
		//len = (ft_strrchr(x, '/')) - x;
		temp = ft_substr(path, 1, strlen(x) - 1);
		new = ft_strjoin(x, temp);
		free(temp);
	}
	else if ((path[0] == '.') && (path[1] == '.'))
	{
		len = (ft_strrchr(x, '/')) - x;
		temp = ft_substr(x, 0, len);
		temp2 = ft_substr(path, 2, ft_strlen(x) - 2);
		new = ft_strjoin(temp, temp2);
		free(temp);
		free(temp2);
	}
	else if ((path[0] == '~') && (path[1] == '\0'))
		new = getenv("HOME");
	else if ((path[0] == '~') && (path[1] != '\0'))
	{
		temp = ft_substr(path, 1, (ft_strlen(path) - 1));
		new = ft_strjoin(getenv("HOME"), temp);
		free(temp);
	}
	else
		new = ft_strdup(path);
	free(x);
	return (new);
}

void	vars_to_env(char *old_pwd, char *pwd, char **our_env)
{
	char	*to_env;
	int		i;

	i = search_in_env(our_env, "OLDPWD", old_pwd);
	if (i == 0)
	{
		while (our_env[i])
			i++;
		to_env = join_env("OLDPWD", old_pwd);
		our_env[i] = to_env;
		our_env[i + 1] = NULL;
	}
	search_in_env(our_env, "PWD", pwd);
}

int	search_in_env(char **our_env, char *var, char *value)
{
	int		i;
	char	*to_env;

	to_env = NULL;
	i = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], var, ft_strlen(var)) == 0
			&& our_env[i][ft_strlen(var)] == '=')
		{
			to_env = join_env(var, value);
			if (!to_env)
				return (0);
			free(our_env[i]);
			our_env[i] = to_env;
			return (1);
		}
		i++;
	}
	return (i);
}
