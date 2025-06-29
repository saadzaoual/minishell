/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:28 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/29 13:41:46 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// int ft_errlen(char **av)
// {
// 	int i = 0;
// 	while(av[i])
// 		i++;
// 	return i;
// }
// int is_check(char *av)
// {
// 	while(av && (*av >= '0' && *av <= '9'))
// 		av++;
// 	return (!*av) ? 0 : 1;
// }
// int	builtin_exit(char **args)
// {
// 	int	code;
// 	int	i;

// 	code = 0;
// 	if (args[1] && !is_check(args[1]))
// 		code = ft_atoi(args[1]) & 0xFF;
// 	else 
// 		code = -1;
// 	i = 1;
// 	printf("exit\n");
// 	if (args[i] && code == -1)
// 	{
// 		printf("bash: exit: %s: numeric argument required\n", args[i]);
// 		exit(2);
// 	}
// 	exit(code);
// }

#include "../execution.h"

static int	is_numeric(const char *s)
{
	if (!s || *s == '\0')
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	int	code;

	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			return (2);
		}
		if (args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		code = ft_atoi(args[1]) & 0xFF;
		return (-42 - code);
	}
	return (-42);
}
