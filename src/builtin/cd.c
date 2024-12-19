/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:19:34 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/19 12:41:24 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
int	cd(char **cmd)
{
	char	*old_pwd;
	char	*pwd;
	char	*path;

	old_pwd = getcwd(NULL, 0);
	path = NULL;
	pwd = NULL;
	if (cmd[2])
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		get_status(1);
		return (0);
	}
	if (!cmd[1])
	{
		path = getenv("HOME");
		if (path == NULL)
			ft_printf_fd(STDERR_FILENO, "cd: could not get the home directory\n");
	}
	else
		path = get_path(cmd[1]);
	
	if (chdir(path) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "cd: no such file or directory\n");
		get_status(1);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	vars_to_env(old_pwd, pwd);
	return (0);
}
*/

int	cd(char **cmd)
{
	char	*old_pwd;
	char	*pwd;
	char	*path;
	char	**our_env;

	our_env = env_shellzito(NULL);
	old_pwd = getcwd(NULL, 0);
	path = NULL;
	pwd = NULL;
	if (cmd[2])
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		get_status(1);
		return (0);
	}
	path = cd_aux(cmd);
	if (chdir(path) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "cd: no such file or directory\n");
		get_status(1);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	vars_to_env(old_pwd, pwd, our_env);
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
		path = get_path(cmd[1]);
	return (path);
}

char	*get_path(char *path)
{
	char	*new;
	char	*x;
	size_t	len;

	new = NULL;
	x = getcwd(NULL, 0);
	if ((path[0] == '.') && (path[1] == '\0'))
		new = x;
	else if ((path[0] == '.') && (path[1] && path[1] != '.'))
	{
		len = (ft_strrchr(x, '/')) - x;
		new = ft_strjoin(x, (ft_substr(path, 1, strlen(x) - 1)));
	}
	else if ((path[0] == '.') && (path[1] == '.'))
	{
		len = (ft_strrchr(x, '/')) - x;
		new = ft_strjoin((ft_substr(x, 0, len)), (ft_substr(path, 2, ft_strlen(x) - 2)));
	}
	else if ((path[0] == '~') && (path[1] == '\0'))
		new = getenv("HOME");
	else if ((path[0] == '~') && (path[1] != '\0'))
		new = ft_strjoin(getenv("HOME"), ft_substr(path, 1, (ft_strlen(path) - 1)));
	else if (path[0] == '/')
		new = ft_strdup(path);
	return (new);
}
/*
void	vars_to_env(char *old_pwd, char *pwd, char **our_env)
{
	int		i;
	int		j;
	char	*to_env;

	to_env = NULL;
	i = 0;
	j = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], "OLDPWD", 5) == 0
			&& our_env[i][6] == '=')
		{
			to_env = join_env("OLDPWD", old_pwd);
			if (!to_env)
				return ;
			free(our_env[i]);
			our_env[i] = to_env;
			j++;
		}
		if (ft_strncmp(our_env[i], "PWD", 2) == 0
			&& our_env[i][3] == '=')
		{
			to_env = join_env("PWD", pwd);
			if (!to_env)
				return ;
			free(our_env[i]);
			our_env[i] = to_env;
		}
		i++;
	}
	if (j == 0)
	{
		to_env = join_env("OLDPWD", old_pwd);
		our_env[i] = to_env;
		our_env[i + 1] = NULL;
	}
}
*/

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
