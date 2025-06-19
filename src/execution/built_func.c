/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:28 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/19 19:04:37 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	builtin_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;	
	}
	if (new_line)
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	builtin_cd(char **args)
{
	const char	*path;

	path = args[1];
	if (!path)
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_exit(char **args)
{
	int	code;

	code = 0;
	if (args[1])
		code = ft_atoi(args[1]);
	printf("exit\n");
	exit(code);
}

int	builtin_env(char **args)
{
	int	i;

	i = 0;
	args = env;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
