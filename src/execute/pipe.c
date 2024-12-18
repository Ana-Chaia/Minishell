/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:40 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/18 12:02:02 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int execute_pipe(t_ast *node, t_minishell *mini)
{
	int		task[2];
	int		status[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!node || !node->left || !node->right)
		return (-1);
	//if (is_redirect(node->left->type) == 1)
		//execution(node->left);
	if (pipe(task) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipe error\n");
		//printf("Shellzito: pipe error \n");
		return (get_status(-1));
	}
	pid1 = fork();
	signal_exec(pid1);
	if (pid1 < 0)	
	{
		ft_printf_fd(STDERR_FILENO, "fork error\n");
		//printf("Shellzito: fork error \n");
		close(task[0]);
		close(task[1]);
		return (get_status(-1));
	}
	else if	(pid1 == 0)
		child_process(task, node->left, 0, mini);
	pid2 = fork();
	signal_exec(pid2);
	if (pid2 < 0)
	{
		ft_printf_fd(STDERR_FILENO, "fork error\n");
		//printf("Shellzito: fork error \n");
		close(task[0]);
		close(task[1]);
		return (get_status(-1));
	}
	else if (pid2 == 0)
		child_process(task, node->right, 1, mini);
	close(task[0]);
	close(task[1]);
	//status = get_status(-1);
	waitpid(pid1, &status[0], 0);
	waitpid(pid2, &status[1], 0);
	//printf("StatusPipe[0]: %d\n", status[0]);
	//printf("StatusPipe[1]: %d\n", status[1]);
	//printf("StatusPipe[1]: %d\n", get_status(-1));
	return (get_status(WEXITSTATUS(status[1])));
}

void child_process(int *task, t_ast *node, int nb_pid, t_minishell *mini)
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





/*
int execute_pipe(t_ast *node)
{
	int		task[2];
	int		status[2];
	pid_t	pid[2];
	
	if (node->left && is_redirect(node->left->type) == 1)
		execution(node->left);
	if (!pipe(task))
	{
		pid[0] = fork();
		if (pid[0] < 0)
			printf("fork error %s\n", node->content);
		signal_exec(pid[0]);
				if (pid[0] == 0 && node->left)
			child_process(task, node->left, 0);
		pid[1] = fork();
		if (pid[1] < 0)
			printf("fork error \n");
		signal_exec(pid[0]);
		if (pid[1] == 0 && node->right)
			child_process(task, node->right, 1);
		close(task[0]);
		close(task[1]);
		waitpid(pid[0], status[0], 0);
		waitpid(pid[1], status[1], 0);
		return
	}
	else
	{
		get_status(status[1]);
		close(task[0]);
		close(task[1]);
	}	
	return (0);
}
*/