/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:59:51 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/07 13:19:50 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int	call_builtins(char *token, t_export **export_list)
int	execute_builtin(char *token_tree, t_minishell *mini)
{
	int		builtin;
	char	**cmd;

	builtin = -1;
	cmd = ft_split(token_tree, ' ');
	if (!cmd || !cmd[0])
		return (builtin);
	if (!ft_strcmp(cmd[0], "echo"))
		builtin = echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
	 	builtin = cd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		builtin = pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		builtin = export(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
	 	builtin = unset(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
	 	builtin = env(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		builtin = the_exit(cmd, mini);
	free_ptrptr(cmd);
	return (builtin);
}

int	echo(char **cmd)
{
	int	new_line;
	int	space;
	int	i;

	i = 1;
	space = 0;
	new_line = 1;
	while (check_minus_nnnns(cmd[i]))
	{
		i++;
		new_line = 0;
	}
	while (cmd[i])
	{
		if (space)
			ft_putchar_fd (' ', 1);
		else
			space++;
		ft_putstr_fd (cmd[i++], 1);
	}
	if (new_line)
		ft_putchar_fd ('\n', 1);
	return (0);
}

int	check_minus_nnnns(char *cmd)
{
	int	i;

	if (cmd && !ft_strncmp(cmd, "-n", 2))
	{
		i = 2;
		while (cmd[i] == 'n')
			i++;
		if (!cmd[i])
			return (1);
	}
	return (0);
}

/*
substituida por free_ptrptr
void	ft_free_split(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
*/
