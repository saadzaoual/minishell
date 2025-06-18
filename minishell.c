/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:21 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/12 19:05:53 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(void)
{
	char *input;
	
	while(1)
	{
		input = readline("mohammedabdoSHELL$ ");
		if(!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
            		add_history(input);
		printf("You Typed %s\n",input);
		free(input);
	}
	return (0);
}
