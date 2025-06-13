/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:21 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/13 16:56:10 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(void)
{
    char *input;
    char **args;
    int i;

    while (1)
    {
        input = readline("minishell$> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);

        args = split_input(input);

        i = 0;
        while (args && args[i])
        {
            printf("Token[%d]: %s\n", i, args[i]);
            i++;
        }

        // Free everything
        i = 0;
        while (args && args[i])
            free(args[i++]);
        free(args);
        free(input);
    }

    return 0;
}
