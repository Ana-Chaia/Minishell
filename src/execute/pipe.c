#include "../include/minishell.h"

int execute_pipe(t_ast *node)
{
	//int		task[2];
	//pid_t	pid[2];
	
//	if (is_redirect(node->left->type) == 1)
//		execution(node->left);
//	if (!pipe(task))
//	{
//		pid[0] = fork();
//		if (pid[0] < 0)
			printf("fork error %s\n", node->content);
//		if (pid[0] == 0)
//			child_process(task, node->left, 0);
//		pid[1] = fork();
//		if (pid[1] < 0)
//			printf("fork error \n");
//		if (pid[1] == 0)
//			child_process(task, node->right, 1);
//		close(task[0]);
//		close(task[1]);
//		waitpid(pid[0],    , 0);
//		waitpid(pid[1],    , 0);
//	}
//	else
//		saída de erro
	return (0);
}

void child_process(int task, t_ast *node, int nb_pid)
{
    printf("chegou aqui %d\n", task);
    printf("chegou aqui %s\n", node->content);
    printf("chegou aqui %d\n", nb_pid);
	
}