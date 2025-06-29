/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:14:41 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/29 13:17:40 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	handle_builtin_in_parent(t_cmd *cmd, t_cmd *head, char *input)
{
	int	ret;
	int	in = dup(STDIN_FILENO);
	int	out = dup(STDOUT_FILENO);

	if (handle_redirections(cmd->redirs))
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(in);
		close(out);
		return (1);
	}
	ret = exec_builtin(cmd);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	if (ret <= -42)
	{
		free_cmd_list(head);
		free(input);
		exit(-(ret + 42));
	}
	return (1);
}

int	execute_command(t_cmd *cmd, t_cmd *head, char *input)
{
	pid_t	pid;

	if (is_builtin(cmd->cmd))
	{
		if (!ft_strncmp(cmd->cmd, "cd", 2) ||
			!ft_strncmp(cmd->cmd, "exit", 4) ||
			!ft_strncmp(cmd->cmd, "export", 6) ||
			!ft_strncmp(cmd->cmd, "unset", 5))
			return (handle_builtin_in_parent(cmd, head, input));
		pid = fork();
		if (pid == 0)
		{
			if (handle_redirections(cmd->redirs))
				exit(1);
			exit(exec_builtin(cmd));
		}
		waitpid(pid, NULL, 0);
	}
	else
		exec_external(cmd);
	return (1);
}
