/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:15:05 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/29 18:48:59 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	the_exit(char **cmd)
{
	int		i;
	int		count;
	int		status;

	status = 42;
	count = 0;
	i = 1;
	while (cmd[i] != NULL)
	{
		while (cmd[count] != NULL)
			count++;
		printf("cmd[count - 1]: %s\n", cmd[count - 1]);
		printf("count: %d\n", count);
		if (count == 2)
		{
			if (verify_args(&cmd[1]) == 1)
				exit (2);
			else
			{
				status = ft_atoi(cmd[1]);
				printf("exit deu certo, status = %d\n", status);
				exit(status);
			}
		}
		else
		{
			if (verify_args(&cmd[1]) == 1)
				exit (2);
			printf("shellzito: exit: %s: too many arguments \n", cmd[i]);
			exit(1);
		}
		i++;
	}
	if (cmd[0] && cmd[1] == NULL)
		exit(status); //pegar o status de final do último cmd, salvar na struct e receber ela;
	//obs: DAR FREE EM TUDO E FECHAR TODOS FDS antes de todos os exits;
	return (0);
}

int	verify_args(char **cmd)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i][j])
	{
		if (is_sign(cmd[i][j]) == 1)
			j++;
		printf("cmd[%d][%d]: %c\n", i, j, cmd[i][j]);
		if (ft_isdigit(cmd[i][j]) == 0)
		{
			printf("shellzito: exit: %s: numeric argument required\n",
				cmd[i]);
			return (1);
		}
		if (is_longer(cmd[i]) == 1)
			return (1);
		j++;
	}
	return (0);
}

int	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	is_longer(char *cmd)
{
	if ((ft_strlen(cmd) == 19 && ft_strncmp(cmd, "9223372036854775807", 19) > 0)
		|| ((ft_strlen(cmd) == 20 && ft_strncmp(cmd, "-9223372036854775808", 20)
				> 0)))
	{
		printf("shellzito: exit: %s: numeric argument required\n", cmd);
		return (1);
	}
	return (0);
}
