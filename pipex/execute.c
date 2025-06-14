/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:54:55 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 16:58:42 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_child(char *cmd, char **envp, int input_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	if (pipe(pipe_fd) == -1)
		error_exit ("Pipe failed\n");
	pid = fork();
	if (pid < 0)
		error_exit ("Fork failed\n");
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		close (pipe_fd[1]);
		args = parse_cmd(cmd);
		cmd_path = find_command_path(args[0], envp);
		execve(cmd_path, args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (pipe_fd[0]);
}

void	execute_last(char *cmd, char **envp, int input_fd, int outfile)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	if (pid < 0)
		error_exit("Fork faild");
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(input_fd, STDOUT_FILENO);
		args = parse_cmd(cmd);
		cmd_path = find_command_path(args[0], envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close (input_fd);
	close (outfile);
	wait (NULL);
}
