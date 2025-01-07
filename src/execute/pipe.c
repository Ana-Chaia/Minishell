/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:40 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/20 16:05:12 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	execute_pipe(t_ast *node, t_minishell *mini)
// {
// 	int		task[2];
// 	int		status[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (!node || !node->left || !node->right)
// 		return (-1);
// 	if (pipe(task) == -1)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "pipe error\n");
// 		return (get_status(-1));
// 	}
// 	pid1 = fork();
// 	signal_exec(pid1);
// 	if (pid1 < 0)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "fork error\n");
// 		close(task[0]);
// 		close(task[1]);
// 		return (get_status(-1));
// 	}
// 	else if (pid1 == 0)
// 		child_process(task, node->left, 0, mini);
// 	pid2 = fork();
// 	signal_exec(pid2);
// 	if (pid2 < 0)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "fork error\n");
// 		close(task[0]);
// 		close(task[1]);
// 		return (get_status(-1));
// 	}
// 	else if (pid2 == 0)
// 		child_process(task, node->right, 1, mini);
// 	close(task[0]);
// 	close(task[1]);
// 	waitpid(pid1, &status[0], 0);
// 	waitpid(pid2, &status[1], 0);
// 	status[1] = WEXITSTATUS(status[1]);
// 	return (get_status(status[1]));
// }
int	execute_pipe(t_ast *node, t_minishell *mini)
{
	int		task[2];
	int		status[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!node || !node->left || !node->right)
		return (-1);
	if (pipe(task) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipe error\n");
		return (get_status(-1));
	}
	pid1 = fork_and_exec(task, node->left, 0, mini);
	if (pid1 < 0)
		return (handle_fork_error(task));
	pid2 = fork_and_exec(task, node->right, 1, mini);
	if (pid2 < 0)
		return (handle_fork_error(task));
	close(task[0]);
	close(task[1]);
	waitpid(pid1, &status[0], 0);
	waitpid(pid2, &status[1], 0);
	status[1] = WEXITSTATUS(status[1]);
	return (get_status(status[1]));
}

pid_t	fork_and_exec(int *task, t_ast *node, int nb_pid, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	signal_exec(pid);
	if (pid == 0)
		child_process(task, node, nb_pid, mini);
	return (pid);
}

int	handle_fork_error(int *task)
{
	ft_printf_fd(STDERR_FILENO, "fork error\n");
	close(task[0]);
	close(task[1]);
	return (get_status(-1));
}

void	child_process(int *task, t_ast *node, int nb_pid, t_minishell *mini)
{
	int	status;

	if (nb_pid == 0)
	{
		close(task[0]);
		dup2(task[1], STDOUT_FILENO);
		close(task[1]);
	}
	else if (nb_pid == 1)
	{
		close(task[1]);
		dup2(task[0], STDIN_FILENO);
		close(task[0]);
	}
	status = execution(node, mini);
	bye_bye(mini);
	rl_clear_history();
	exit(status);
}
