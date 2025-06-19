/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:29:35 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/19 19:09:51 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(cmd, "env", 3))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (!ft_strcmp(cmd->cmd, "echo", 4))
		return (builtin_echo(cmd->args));
	if (!ft_strcmp(cmd->cmd, "cd", 2))
		return (builtin_cd(cmd->args));
	if (!ft_strcmp(cmd->cmd, "pwd", 3))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->cmd, "export", 6))
		return (builtin_export(cmd->args));
	if (!ft_strcmp(cmd->cmd, "unset", 5))
		return (builtin_unset(cmd->args));
	if (!ft_strcmp(cmd->cmd, "env", 3))
		return (builtin_env(env));
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (builtin_exit(cmd->args));
	return (1);
}
