/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:29:41 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/15 17:56:32 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"

int		builtins(char *cmd);
int		echo_builtins(char **args);
int		cd_builtins(char **args);
int		pwd_builtins(void);
void	exit_builins(char **args);
int		ft_strcmp(const char *s1, const char *s2);

#endif