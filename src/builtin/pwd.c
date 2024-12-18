/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:21:38 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/18 11:56:14 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Print the absolute pathname of the current working directory. If the -P
// option is supplied, the pathname printed will not contain symbolic links.
// If the -L option is supplied, the pathname printed may contain symbolic
// links. The return status is zero unless an error is encountered while 
// determining the name of the current directory or an invalid option is
// supplied.

#include "../include/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_printf_fd(STDERR_FILENO, "pwd: error retrieving current directory\n");
		//perror("pwd: error retrieving current directory \n");
		return (get_status(-1));
	}
	printf("%s\n", path);
	free(path);
	return (get_status(0));
}

// Obs:
// anacaro5@c1r7p3:~$ PWD
// PWD: comando não encontrado
// anacaro5@c1r7p3:~$ UNSET
// UNSET: comando não encontrado
// anacaro5@c1r7p3:~$ ECHO $?
// ECHO: comando não encontrado
// anacaro5@c1r7p3:~$ echo $?
// 127

