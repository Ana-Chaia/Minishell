/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:21:38 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/19 12:35:11 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_printf_fd(STDERR_FILENO, "pwd: error retrieving current directory\n");
		return (get_status(-1));
	}
	printf("%s\n", path);
	free(path);
	return (get_status(0));
}
