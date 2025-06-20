/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:28 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/20 17:35:57 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_errlen(char **av)
{
	int i = 0;
	while(av[i])
		i++;
	return i;
}
int is_check(char *av)
{
	while(av && (*av >= '0' && *av <= '9'))
		av++;
	return (!*av) ? 0 : 1;
}
int	builtin_exit(char **args)
{
	int	code;
	int	i;
	code = 0;
	if (args[1] && !is_check(args[1]))
		code = ft_atoi(args[1]) & 0xFF;
	else 
		code = -1;
	i = 1;
	printf("exit\n");
	if (args[i] && code == -1)
	{
		printf("bash: exit: %s: numeric argument required\n", args[i]);
		exit(2);
	}
	exit(code);
}
