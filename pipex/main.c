/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:29:09 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 17:26:07 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		ft_printf("Error: Add more arguments!\n");
		return (1);
	}
	handle_pipex(ac, av, envp);
	return (0);
}
