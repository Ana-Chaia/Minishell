/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:28 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/12 11:35:14 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_builtin(t_ast *node, t_minishell *mini)
{
	int		builtin;
	char	**cmd;

	builtin = -1;
	//cmd = ft_split(token_tree, ' ');
	cmd = node->cmd_args;
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
	//free_ptrptr(cmd);
	return (builtin);
}
