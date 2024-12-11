/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:16:09 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/07 13:00:17 by anacaro5         ###   ########.fr       */
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
	fprintf(stderr, "|----------|---------------|------|----------|--------|----------|\n");
	fprintf(stderr, "| position |    content    | type |   prev   |   curr |   next   |\n");
	fprintf(stderr, "|----------|---------------|------|----------|--------|----------|\n");
	while (curr)
	{
		fprintf(stderr, "| %8d | %13s | %4d | %2p   | %2p | %2p   |\n", curr->position, curr->content, curr->type, curr->prev, curr, curr->next);
		curr = curr->next;
	}
	fprintf(stderr, "|----------|---------------|------|----------|--------|---------|\n\n");
	fflush(stderr);
}

void	print_env_copy(char **copy)
{
	int	i;

	i = 0;
	if (copy == NULL)
		printf("array envcopy vazio\n");
	while (copy[i])
	{
		printf("env_copy: %s\n", copy[i]);
		i++;
	}
}

void	print_tree(t_ast *root, int nivel)
{
	int	i;

	if (root)
	{
		print_tree(root->right, nivel + 1);
		printf("\n\n");
		for(i = 0; i < nivel; i++)  //APAGAR
			printf("\t");
		printf("%s - %d", root->content, root->type);
		print_tree(root->left, nivel + 1);
		printf("\n\n");
	}
}
