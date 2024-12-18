/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:10:38 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/18 17:44:34 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_redirect(t_ast *node, t_minishell *mini)
{
	int	svd_stdin;
	int	svd_stdout;
	int	fd;

	fd = 0;
	svd_stdin = dup(STDIN_FILENO);
	svd_stdout = dup(STDOUT_FILENO);
	fd = open_file(node, &svd_stdin, &svd_stdout);
	if (fd != -1)
	{
		dup_dup(node, &fd);
		if (node->left)
			execution(node->left, mini);
		dup2(svd_stdin, STDIN_FILENO);
		close(svd_stdin);
		dup2(svd_stdout, STDOUT_FILENO);
		close(svd_stdout);
		printf("fd1: %d\n", fd);
		return (0);
	}
	printf("fd2: %d\n", fd);
	return (1);
}

int	open_file(t_ast *node, int *svd_stdin, int *svd_stdout)
{
	int	fd;
	int a;

	a = 0;
	fd = 0;
	if (node && (node->type == RED_IN || node->type == HEREDOC))
	{
		fd = open(node->right->content, O_RDONLY);
		//printf("FD_OPEN_FILE: %d, node: %s, right: %s\n", fd, node->content, node->right->content);
		if (fd == -1)
		{
			close(STDIN_FILENO);
			dup2(*svd_stdin, STDIN_FILENO);
			ft_printf_fd(STDERR_FILENO, "%s: %s\n", node->right->content, strerror(errno));
			//ft_printf("Shellzito: %s: %s\n", node->right->content, strerror(errno));
			get_status(1);
			return (fd);
		}
	}
	else if (node && (node->type == RED_OUT))
		fd = open(node->right->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node && (node->type == APPEND))
		fd = open(node->right->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		close(STDIN_FILENO);
		dup2(*svd_stdin, STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(*svd_stdout, STDOUT_FILENO);
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", node->right->content, strerror(errno));
		//ft_printf("Shellzito: %s: %s\n", node->right->content, strerror(errno));
		a = get_status(1);
		ft_printf("status: %d\n", a);
		return (fd);
	}
	return (fd);
}

int	dup_dup(t_ast *node, int *fd)
{
	if (node && (node->type == RED_IN || node->type == HEREDOC))
	{
		if (*fd != 1 && *fd != STDIN_FILENO)
		{
			dup2(*fd, STDIN_FILENO);
			close(*fd);
			return (0);
		}
	}
	else if (node && (node->type == RED_OUT || node->type == APPEND))
	{
		if (*fd != 1 && *fd != STDOUT_FILENO)
		{
			dup2(*fd, STDOUT_FILENO);
			close(*fd);
			return (0);
		}
	}
	return (-1);
}
