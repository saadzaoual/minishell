/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:34:26 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/15 17:55:15 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_builtins(char **args)
{
	if (!args)
	{
		printf("cd: missing argument\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror ("cd");
		return (1);
	}
	return (0);
}
