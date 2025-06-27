/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:55:02 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/20 16:42:06 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i + 1);
}

void	remove_env_var(const char *key)
{
	int		i;
	int		j;
	size_t	len;
	char	**new_env;

	len = ft_strlen(key);
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=') break ;
	if (!env[i])
		return ;
	new_env = malloc(sizeof(char *) * ft_env_size(env));
	if (!new_env)
		return ;
	j = 0;
	while (env[j])
	{
		if (j != i)
			new_env[j - (j > i)] = env[j];
		j++;
	}
	new_env[j - 1] = NULL;
	free(env[i]);
	free(env);
	env = new_env;
}

int	builtin_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(args[i]);
		i++;
	}
	return (0);
}
