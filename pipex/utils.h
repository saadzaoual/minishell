/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:29:02 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 17:15:09 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "pipex.h"

void	error_exit(const char *msg);
void	free_array(char **arr);
char	*get_env_path(char **envp);
char	*find_command_path(char *cmd, char **envp);

#endif