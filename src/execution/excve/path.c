/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:01:09 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/25 20:58:54 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;
	char	len1;
	char	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(joined, s1, len1 + 1);
	ft_strlcat(joined, s2, len1 + len2 + 1);
	free(s1);
	return (joined);
}

char	*get_cmd_path(t_cmd *cmd)
{
	char	**paths;
	char	*path_env;
	char	*path_try;
	int		i;

	if (!cmd || !cmd->cmd)
		return (NULL);
	if (access(cmd->cmd, X_OK) == 0)
		return (ft_strdup(cmd->cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path_try = ft_strjoin(paths[i], "/");
		path_try = ft_strjoin_free(path_try, cmd->cmd);
		if (access(path_try, X_OK) == 0)
			return (free_split(paths), path_try);
		free(path_try);
	}
	return (free_split(paths), NULL);
}
