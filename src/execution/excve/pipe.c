/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:03:03 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/29 17:25:39 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	child_process(t_cmd *cmd, int prev_fd, int *fd)
{
	char *path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}

	if (handle_redirections(cmd->redirs))
		exit(1);

	if (is_builtin(cmd->cmd))
		exit(exec_builtin(cmd));

	path = get_cmd_path(cmd);
	if (!path)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(path, cmd->args, env);
	perror("execve");
	exit(1);
}

void	handle_parent(int *prev_fd, int *fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(fd[1]);
	*prev_fd = fd[0];
}

int	execute_pipeline(t_cmd *cmd)
{
	int		fd[2];
	int		prev_fd = -1;
	pid_t	pid;
	t_cmd	*curr = cmd;

	while (curr)
	{
		if (curr->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		else if (pid == 0)
			child_process(curr, prev_fd, fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (curr->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		curr = curr->next;
	}
	while (wait(NULL) > 0) ;
	return (0);
}
