/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:04:31 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/29 13:40:17 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../includes/minishell.h"
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;

/* Builtins */
int		exec_builtin(t_cmd *cmd);
int		is_builtin(char *cmd);
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_env(char **env);
int		builtin_exit(char **args);

/* Environment Handling */
char	**copy_env(char **envp);
void	free_env(char **envp);
int		ft_env_size(char **envp);
int		update_env_var(char *arg);
void	remove_env_var(const char *key);

/* Export/Unset Helpers */
char	*extract_key(char *arg);
char	**expand_env(char *arg, char *key, int i);

/* Command Execution */
char    *get_cmd_path(t_cmd *cmd);
int     exec_external(t_cmd *cmd);
int		handle_builtin_in_parent(t_cmd *cmd, t_cmd *head, char *input);
int		execute_command(t_cmd *cmd, t_cmd *head, char *input);

/* Handle Redirection and Heredoc */
int	has_redir(t_cmd *cmd);
int	open_heredoc(char *delimiter);
int	handle_redirections(t_redir *redir);

#endif
