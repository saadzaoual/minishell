/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:29:09 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/14 17:10:59 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_pipex(int ac, char **av, char **envp)
{
	int	infile;
	int	outfile;
	int	prev_fd;
	int	i;

	infile = open (av[1], O_RDONLY);
	outfile = open (av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = 2;
	prev_fd = infile;
	if (infile < 0 || outfile < 0)
		error_exit("Error: file open failed!\n");
	while (i < ac - 2)
	{
		prev_fd = execute_chiled(av[i], envp, prev_fd);
		i++;
	}
	execute_last(av[i], envp, prev_fd, outfile);
}

int main(int ac, char **av, char **envp)
{
	if (ac < 6)
	{
		ft_printf("Error: Add more arguments!\n");
		return (1);
	}
	handle_pipex(ac, av, envp);
}
