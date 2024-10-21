#include "../include/minishell.h"

//na main tem que ter envp como variavel

void	copy_env()
{
	char	**our_env;
	int		i;

	i = 0;
	while (__environ[i])
		i++;
	our_env = malloc (sizeof(char*) * (i + 1));
	i = 0;
	while (__environ[i])
	{
		our_env[i] = ft_strdup(__environ[i]);
		if (!our_env[i])
		{
			free_env(our_env);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	our_env[i] = NULL;
	print_env_copy(our_env);
	// env_shellzito(our_env);
}

void	free_env(char **array)
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
}

// char	**env_shellzito(char **our_env)
// {
// 	static char	**env_shellzito;

// 	// if (our_env && env_shellzito)
// 	// 	ft_free_list(&env_shellzito);
// 	if (our_env)
// 		env_shellzito = our_env;
// 	print_env_copy(env_shellzito);
// 	return (env_shellzito);
// }




// usar getenv