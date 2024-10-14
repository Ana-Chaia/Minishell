/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:16:09 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/05 15:25:34 by anacaro5         ###   ########.fr       */
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
// # define SPACES 4
// # define CYAN "\033[36m"
// # define RESET "\033[0m"


// static void	print_tree(t_btree *root, int distance, t_var_types type);

// void		visualize_tree(t_btree *root, t_var_types type)
// {
// 	printf(CYAN "Tree visualization:\n\n\n" RESET);
// 	print_tree(root, 0, type);
// 	printf("\n\n");
// }

// static void	print_tree(t_btree *root, int distance, t_var_types type)
// {
// 	if (root == NULL)
// 		return ;
// 	distance += SPACES;
// 	print_tree(root->right, distance, type);
// 	print_right_branch(distance + 2, root->right);
// 	print_item(root, type, distance);
// 	print_left_branch(distance + 2, root->left);
// 	print_tree(root->left, distance, type);
// }
// void	print_distance(int distance)
// {
// 	for (int i = SPACES; i < distance; i++)
// 		printf(" ");
// }

// void print_right_branch(int distance, t_btree *right)
// {
// 	if (!right)
// 		return ;
// 	print_distance(distance);
//     printf("/\n");
// }

// void print_left_branch(int distance, t_btree *left)
// {
// 	if (!left)
// 		return ;
// 	print_distance(distance);
//     printf("\\\n");
// }

// void	print_item(t_btree *this_node, t_var_types type, int distance)
// {
// 	print_distance(distance);
// 	if (INT == type)
// 		printf("%d\n", *(int *)this_node->item);
// 	else if (CHAR == type)
// 		printf("%s\n", (char *)this_node->item);
// }














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
