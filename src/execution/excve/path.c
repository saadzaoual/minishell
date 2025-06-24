/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:01:09 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/24 15:30:38 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

char	*get_cmd_path(t_cmd *cmd)
{
	char	*prefix = "/usr/bin";
	size_t	full_len;
	char	*full_path;

	if (!cmd || !cmd->cmd)
		return (NULL);
	if (access(cmd->cmd, X_OK) == 0)
		return (ft_strdup(cmd->cmd));
	full_len = ft_strlen(prefix) + ft_strlen(cmd->cmd) + 1;
	full_path = malloc(full_len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, prefix, full_len);
	ft_strlcat(full_path, cmd->cmd, full_len);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
