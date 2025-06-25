/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:53:51 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/25 19:42:15 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**copy;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			free_env(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int	builtin_env(char **args)
{
	int	i;

	i = 0;
	args = env;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (0);
}
