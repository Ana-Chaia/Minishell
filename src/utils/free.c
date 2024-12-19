/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:12:08 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/19 11:53:03 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokenlist(t_token *tokenlist)
{
	t_token	*curr;
	t_token	*next;

	curr = tokenlist;
	if (tokenlist == NULL)
		return ;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
		{
			free(curr->content);
			curr->content = NULL;
			curr->next = NULL;
			curr->prev = NULL;
		}
		if (curr->cmd_args)
			free_ptrptr(curr->cmd_args);
		free(curr);
		curr = next;
	}
	//free(tokenlist);
	//tokenlist = NULL;
}

void	free_export(t_exp *export_list)
{
	t_exp	*curr;
	t_exp	*next;

	curr = export_list;
	if (export_list == NULL)
		return ;
	while (curr)
	{
		next = curr->next;
		if (curr->name)
		{
			free(curr->name);
			curr->name = NULL;
		}
		if (curr->value)
		{
			free(curr->value);
			curr->value = NULL;
		}
		curr->next = NULL;
		curr->prev = NULL;
		free(curr);
		curr = next;
	}
	//free(export_list);
	//export_list = NULL;
}

void	free_ast(t_ast *ast_node)
{
	if (ast_node == NULL)
		return ;
	if (ast_node->left)
	{
		free_ast(ast_node->left);
		//ast_node->left = NULL;
	}
	if (ast_node->right)
	{
		free_ast(ast_node->right);
		//ast_node->right = NULL;
	}
	if (ast_node->content)
		free(ast_node->content);
	if (ast_node->first_cmd)
		free(ast_node->first_cmd);
	if (ast_node->exec_ready)
		free(ast_node->exec_ready);
	//if (ast_node->cmd_args)
	//	free_ptrptr(ast_node->cmd_args);
	if (ast_node->path_array)
		free_ptrptr(ast_node->path_array);
	free(ast_node);
	ast_node = NULL;
}

void	free_mini(t_minishell *mini)
{
	if (mini->input)
		free(mini->input);
	if (mini->tree)
	{
		free_ast(mini->tree);
		//free(mini->tree);
		//mini->tree = NULL;
	}
	if(mini->export_list)
	{
		free_export(mini->export_list);
		mini->export_list = NULL;
		//printf("DEU FREE NO EXPORTLIST");
	}
	if (mini->tokenlist)
	{
		free_tokenlist(mini->tokenlist);
		//free(mini->tokenlist);
		mini->tokenlist = NULL;
		//printf("DEU FREE NO TOKENLIST");
	}
}


void	bye_bye(t_minishell *mini)
{
	char	**env_copy;
	int		fd;

	fd = STDIN_FILENO;
	env_copy = env_shellzito(NULL);
	printf("ENTROU AQUI: %d\n", fd);   //apagar
	if (mini->input)
		free(mini->input);
	if (env_copy)
		free_ptrptr(env_copy);
	if (mini->tree)
	{
		free_ast(mini->tree);
		//free(mini->tree);
	}		
	if (mini->export_list)
	{
		free_export(mini->export_list);
//		free(mini->export_list);
	}
	if (mini->tokenlist)
		free_tokenlist(mini->tokenlist);
	if (mini)
		free(mini);
	close_fds(fd);
}

void	free_ptrptr(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

// void	clear_and_free(t_minishell *mini)
// {
// 	rl_clear_history();
// 	printf("exit\n");    //vf no bash "exit" ou "shellzito: exit"
// 	if (mini->input)
// 		free(mini->input);
// 	free(mini);
// 	return ;
// }


int	ft_flags(int fd, char flag, va_list args)
{
	if (flag == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	if (flag == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	if (flag == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

int	ft_printf_fd(int fd, const char *type_format, ...)
{
	va_list	args;
	int		i;
	int		result;

	i = 0;
	result = 0;
	if (!type_format)
		return (-1);
	va_start(args, type_format);
	while (type_format[i])
	{
		if (type_format[i] == '%' && type_format[i + 1] != '\0')
			result += ft_flags(fd, type_format[++i], args);
		else
			result += ft_putchar_fd(type_format[i], fd);
		i++;
	}
	va_end(args);
	return (result);
}
