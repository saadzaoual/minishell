/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@students.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:21 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/14 21:22:55 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(void)
{
    char *input;
    char **tokens;
    int cmd_count;
    char ***split_cmds;
    t_cmd *cmd;

    while (1)
    {
        input = readline("minishell$> ");
        if (!input)
            break;

        if (*input)
            add_history(input);

        tokens = split_input(input);
        if (!tokens)
        {
            free(input);
            continue;
        }

        split_cmds = split_by_pipe(tokens, &cmd_count);

        for (int i = 0; i < cmd_count; i++)
        {
            cmd = parse_tokens(split_cmds[i]);
            if (cmd)
            {
                printf("CMD[%d]: %s\n", i, cmd->cmd);
                for (int j = 0; cmd->args && cmd->args[j]; j++)
                    printf("Arg[%d]: %s\n", j, cmd->args[j]);

                if (cmd->infile)
                    printf("Infile: %s\n", cmd->infile);

                for (int o = 0; o < cmd->out_count; o++)
                    printf("Outfile[%d]: %s (append: %d)\n", o, cmd->outfiles[o], cmd->append_flags[o]);

                free_cmd(cmd);
            }

            // free split_cmds[i]
            for (int k = 0; split_cmds[i][k]; k++)
                free(split_cmds[i][k]);
            free(split_cmds[i]);
        }

        free(split_cmds);

        for (int i = 0; tokens[i]; i++)
            free(tokens[i]);
        free(tokens);
        free(input);
    }

    printf("exit\n");
    return 0;
}
