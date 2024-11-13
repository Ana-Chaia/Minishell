#include "../include/minishell.h"

void    execution(t_ast *node)
{
    if (node->type == PIPE)
		execute_pipe(node);  
   // if (is_redirect(node->type) == 1)   //ajustar is_redirect para int (e enviar curr->type)
   // 	execute_redirect(node);
	else
    {
		if (is_builtin(node->content) == 1)
			printf("isbuiltin working\n");
    		execute_builtin (node->content);  //call_builtins
	//	else
	//		execute_others (node, node->content);
	}
}

int	is_builtin(char *cmd)
{
	size_t	len;

	len = (ft_strchr(cmd, ' ') - cmd);
	if (len == 0)
		return (0);
	if (strncmp(cmd, "echo", len) == 0 
		|| strncmp(cmd, "cd", len) == 0 
		|| strncmp(cmd, "pwd", len) == 0 
		|| strncmp(cmd, "export", len) == 0 
		|| strncmp(cmd, "unset", len) == 0 
		|| strncmp(cmd, "env", len) == 0 
		|| strncmp(cmd, "exit", len) == 0)
		return (1);
	return (0);
}

