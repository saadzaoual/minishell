/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:29:06 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 21:56:48 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_cmd(char *cmd)
{
	char    **args;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		printf("parse_cmd: invalid command\n");
		exit(EXIT_FAILURE);
	}
	return (args);
}
