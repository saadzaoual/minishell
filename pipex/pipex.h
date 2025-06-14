/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:27:41 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/13 22:00:11 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "includes/ft_printf.h"
# include "includes/libft.h"
# include "utils.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32"

char	*find_command_path(char *cmd, char **envp);
char	**parse_cmd(char *cmd);
void	handle_pipex(int ac, char **av, char **envp);
int		execute_child(char *cmd, char **envp, int input_fd);
void	execute_last(char *cmd, char **envp, int input_fd, int outfile);

#endif