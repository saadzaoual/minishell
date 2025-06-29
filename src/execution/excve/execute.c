/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:19:09 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/29 15:20:32 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	child_exec(t_cmd *cmd, char *path)
{
	if (handle_redirections(cmd->redirs))
		exit(1);
	execve(path, cmd->args, env);
	perror(cmd->cmd);
	exit(1);
}

pid_t	prepare_and_fork(t_cmd *cmd, char **path)
{
	pid_t	pid;

	if (!cmd || !cmd->cmd)
		return (write(2, "minishell: command not found\n", 30), -127);
	*path = get_cmd_path(cmd);
	if (!(*path))
	{
		write (2, cmd->cmd, ft_strlen(cmd->cmd));
		write (2, ": command not found\n", 20);
		return (-127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(*path);
		return (-1);
	}
	return (pid);
}

int	exec_external(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	pid = prepare_and_fork(cmd, &path);
	if (pid == -127 || pid == -1)
	{
		if (pid < 0)
			return (1);
		else
			return (127);
	}
	if (pid == 0)
		child_exec(cmd, path);
	waitpid(pid, &status, 0);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
