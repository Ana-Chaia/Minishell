/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:16:09 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/04 18:04:18 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	list_size(t_token *list)
{
	int		list_size;
	t_token	*curr;

	list_size = 0;
	curr = list;
	while (curr)
	{
		curr = curr->next;
		list_size++;
	}
	return (list_size);
}

void	list_printer(t_token *list)
{
	int		list_len;
	t_token	*curr;

	curr = list;
	list_len = list_size(list);
	fprintf(stderr, "List size: %d\n", list_len);
	fprintf(stderr, "List content:\n");
	fprintf(stderr, "|----------|---------------|------|----------|----------|\n");
	fprintf(stderr, "| position |    content    | type |   prev   |   next   |\n");
	fprintf(stderr, "|----------|---------------|------|----------|----------|\n");
	while (curr)
	{
		fprintf(stderr, "| %8d | %13s | %4d | %2p   | %2p   |\n", curr->position, curr->content, curr->type, curr->prev, curr->next);
		curr = curr->next;
	}
	fprintf(stderr, "|----------|---------------|------|----------|----------|\n\n");
	fflush(stderr);
}



// void	ft_tree_printer(t_ast *root)
// {
// 	t_token	*current_command;
// 	t_token	*next_command;

// 	if (root == NULL)
// 		return ;
// 	if (root->type != 0)
// 	{
// 		fprintf(stderr, "|___________________________________________________|\n");
// 		fprintf(stderr, "|			R.O.O.T.		    |\n");
// 		fprintf(stderr, "|...........///				\\\\\\.........|\n");
// 		fprintf(stderr, "|%27s\n", root->content);
// 	}
// 	else
// 		fprintf(stderr, "|%27s\n", root->content);
// 	current_command = root->content;
// 	while (current_command)
// 	{
// 		fprintf(stderr, "|%25s\n", current_command->content);
// 		next_command = current_command->next;
// 		free(current_command);
// 		current_command = next_command;
// 	}
// 	if (root->left)
// 	{
// 		fprintf(stderr, "\033[0;32m\n");
// 		fprintf(stderr, "|__________________________________________________|\n");
// 		fprintf(stderr, "|-----L.E.F.T.-------------------------------------|\n");
// 		ft_tree_printer(root->left);
// 		free(root->left);
// 		root->left = NULL;
// 	}
// 	if (root->right)
// 	{
// 		fprintf(stderr, "\033[0;33m\n");
// 		fprintf(stderr, "|__________________________________________________|\n");
// 		fprintf(stderr, "|-----------------------------------R.I.G.H.T.-----|\n");
// 		ft_tree_printer(root->right);
// 		free(root->right);
// 		root->right = NULL;
// 	}
// 	fflush(stderr);
// 	free(root);
// }
