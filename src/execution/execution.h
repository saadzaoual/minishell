/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:04:31 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/18 20:52:53 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../includes/minishell.h" 
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd);
char	get_cmd_path(char *cmd, char **env);
void	handle_redirections(t_redir *redirs);
void	close_all_pipes(int **pipes, int count);
char	**copy_env(char **envp);

//buitlins function
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_env(char **env);
int		builtin_exit(char **args);

#endif