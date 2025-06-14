/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:29:12 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 17:08:18 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	error_exit(const char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write (1, &msg[i], 1);
		i++;
	}
	exit (1);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*joined;
	char	*full_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	paths = ft_split(get_env_path(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(joined, cmd);
		free(joined);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (free_array(paths), NULL);
}
