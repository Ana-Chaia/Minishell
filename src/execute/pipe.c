#include "../include/minishell.h"

int execute_pipe(t_ast *node)
{
	int		task[2];
	int		status[2];
	pid_t	pid[2];

	if (!node || !node->left || !node->right)
	return (-1);
	//if (is_redirect(node->left->type) == 1)
		//execution(node->left);
	if (pipe(task) == -1)
	{
		printf("pipe error \n");
		return (-1);		
	}
	pid[0] = fork();
	signal_exec(pid[0]);
	if (pid[0] < 0)	
	{
		printf("fork error \n");
		close(task[0]);
		close(task[1]);
		return (-1);
	}
	else if	(pid[0] == 0)
		child_process(task, node->left, 0);
	pid[1] = fork();
	signal_exec(pid[1]);
	if (pid[1] < 0)
	{
		printf("fork error \n");
		close(task[0]);
		close(task[1]);
		return (-1);
	}
	else if (pid[1] == 0)
		child_process(task, node->right, 1);
	close(task[0]);
	close(task[1]);
	//status = status_shellzito(-1);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	return (status_shellzito(status[1]));
}

void child_process(int *task, t_ast *node, int nb_pid)
{
   // printf("chegou aqui %d\n", task);
    printf("chegou aqui %s\n", node->content);
    printf("chegou aqui %d\n", nb_pid);
	if(nb_pid == 0)
	{
		close(task[0]);
		//dup2(task[1], STDOUT_FILENO);
		dup2(task[1], STDOUT_FILENO);
		close(task[1]);
	}	
	else if (nb_pid == 1)
	{
		close(task[1]);
		//dup2(task[0], STDIN_FILENO);
		dup2(task[0], STDIN_FILENO);
		close(task[0]);
	}
	execution(node);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status_shellzito(-1));
}

//para o arquivo signal:
void	signal_exec(int pid)
{
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, signal_handler);
	}
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		signal(SIGPIPE, SIG_IGN);
	}
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
		status_shellzito(status[1]);
		close(task[0]);
		close(task[1]);
	}	
	return (0);
}
*/