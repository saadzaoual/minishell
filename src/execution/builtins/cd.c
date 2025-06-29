/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:33:32 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/29 13:41:30 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	builtin_cd(char **args)
{
	const char	*path;

	path = args[1];
	if (!path)
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
