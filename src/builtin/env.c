#include "../include/minishell.h"

int	env(char **cmd)
{
	int		i;
	char	**our_env;

	i = 0;
	if (cmd[1])
	{
		printf("no options or arguments");
		return (0);
	}
	our_env = env_shellzito(NULL);
	while (our_env[i])
	{
		if (our_env[i] && ft_strchr(our_env[i], '='))
			printf("%s\n", our_env[i]);
		i++;
	}
	return (1);
}
