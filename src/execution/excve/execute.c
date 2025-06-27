/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:19:09 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/25 21:13:34 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	exec_external(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!cmd || !cmd->cmd)
		return (write(2, "minishell: command not found\n", 30), 127);

	path = get_cmd_path(cmd);
	if (!path)
		return (write(2, cmd->cmd, ft_strlen(cmd->cmd)),
			write(2, ": command not found\n", 20), 127);

	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(path), 1);

	if (pid == 0)
	{
		execve(path, cmd->args, env);
		perror(cmd->cmd);
		free(path);
		exit(1);
	}

	waitpid(pid, &status, 0);
	free(path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

