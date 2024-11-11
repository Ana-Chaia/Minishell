#include "../include/minishell.h"

/*
◦ cd with only a relative or absolute path
caminho absoluto -  localização exata de um arquivo ou diretório
 a partir do diretório raiz do sistema (/). Ele sempre começa com /
  e fornece o caminho completo desde a raiz até o diretório ou 
  arquivo desejado.
caminho relativo - localização de um diretório ou arquivo em 
relação ao diretório atual. Ele não começa com / e usa referências
como . (diretório atual) , .. (diretório anterior) para navegar e ~ (diretorio home)

cd nome - procura dentro do diretorio atual
cd ../nome - um nivel acima

na env tem:
OLDPWD vazia no início


*/

int	cd(char **cmd)
{
	char	*old_pwd;
	char	*pwd;
	char	*path;

	old_pwd = getcwd(NULL, 0);
	path = NULL;
	pwd = NULL;
	if (cmd[2])
	{
		printf("cd: too many arguments\n");		//pode usar uma função de printar com fd
		return (0);
	}
	if (!cmd[1])
	{
		path = getenv("HOME");
		if (path == NULL)
			printf("cd: Could not get the home directory.\n");
		//	printf("home_path = %s\n", path);
	}	
	else 
	{
		path = get_path(cmd[1]);
	}
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", pwd);
		return (0);
	}	
	pwd = getcwd(NULL, 0);
	printf("old_pwd: %s\n", old_pwd); 	//apagar
	printf("pwd: %s\n", pwd);			//apagar
	vars_to_env(old_pwd, pwd);
	return (0);
}
	
char *get_path(char *path)
{
	char	*new_path;
	char	*x;
	size_t	len;
	
	x = getcwd(NULL, 0);
	if ((path[0] = '.') && (path[1] == '\0'))
		new_path = x;
	else if ((path[0] = '.') && (path[1] && path[1] != '.'))
	{
		len = (ft_strrchr(x, '/')) - x;
		new_path = ft_strjoin(x, (ft_substr(path, 1, strlen(x) - 1)));
	}	
	else if ((path[0] = '.') && (path[1] == '.'))
	{
		len = (ft_strrchr(x, '/')) - x;
		new_path = ft_strjoin((ft_substr(x, 0, len)), (ft_substr(path, 2, strlen(x) - 2)));
	}	
	else if ((path[0] = '~') && (path[1] == '\0'))
		new_path = getenv("HOME");
	else if ((path[0] = '~') && (path[1] != '\0'))
		new_path = ft_strjoin(getenv("HOME"), ft_substr(path, 1, (ft_strlen(path) - 1)));
	printf("new_path: %s\n", new_path);		//apagar
	return (new_path);
}

void	vars_to_env(char *old_pwd, char *pwd)
{
	char	**our_env;
	int		i;
	int		j;
	char	*to_env;

	our_env = env_shellzito(NULL);
	to_env = NULL;
	i = 0;
	j = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], "OLDPWD", 5) == 0
			&& our_env[i][6] == '=')
		{
			to_env = join_env("OLDPWD", old_pwd);
			if (!to_env)
				return ;
			free(our_env[i]);
			our_env[i] = to_env;
			j++;
		}
		if (ft_strncmp(our_env[i], "PWD", 2) == 0
			&& our_env[i][3] == '=')
		{
			to_env = join_env("PWD", pwd);
			if (!to_env)
				return ;
			free(our_env[i]);
			our_env[i] = to_env;
		}
		i++;
	}
	if (j == 0)
	{
		to_env = join_env("OLDPWD", old_pwd);
		our_env[i] = to_env;
		our_env[i + 1] = NULL;
	}	
}



