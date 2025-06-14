/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:54:55 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 17:49:15 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_pipex(int ac, char **av, char **envp)
{
	int	in_fd;
	int	out_fd;
	int	prev_fd;
	int	i;

	in_fd = open(av[1], O_RDONLY);
	out_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (in_fd < 0 || out_fd < 0)
		error_exit("Error: file open failed!\n");
	prev_fd = in_fd;
	i = 2;
	while (i < ac - 2)
		prev_fd = execute_child(av[i++], envp, prev_fd);
	execute_last(av[i], envp, prev_fd, out_fd);
}

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

void	execute_last(char *cmd, char **envp, int in_fd, int out_fd)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		error_exit("Fork faild");
	if (pid == 0)
	{
		dup2(in_fd, STDIN_FILENO);
		dup2(out_fd, STDOUT_FILENO);
		args = parse_cmd(cmd);
		cmd_path = find_command_path(args[0], envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close (in_fd);
	close (out_fd);
	wait (NULL);
}
