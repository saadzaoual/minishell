/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:27:41 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/15 17:44:40 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins(char *cmd)
{
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "cd") || !strcmp(cmd, "echo") || !strcmp(cmd, "pwd")
		|| !strcmp(cmd, "export") || !strcmp(cmd, "unset")
		|| !strcmp(cmd, "env") || !strcmp(cmd, "exit"));
}
