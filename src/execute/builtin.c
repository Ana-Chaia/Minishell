/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:28 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/11 09:11:31 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		builtin = export(cmd, mini);
	else if (!ft_strcmp(cmd[0], "unset"))
	 	builtin = unset(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
	 	builtin = env(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		builtin = the_exit(cmd, mini);
	free_ptrptr(cmd);
	return (builtin);
}