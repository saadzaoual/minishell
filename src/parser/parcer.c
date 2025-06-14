/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@students.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:30:16 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/14 21:24:56 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../../includes/parser.h"

#define MAX_CMDS 64
#define MAX_TOKENS 256

char ***split_by_pipe(char **tokens, int *cmd_count)
{
    char ***commands = malloc(sizeof(char **) * MAX_CMDS);
    if (!commands)
        return NULL;

    int i = 0, j = 0, k = 0;

    commands[k] = malloc(sizeof(char *) * MAX_TOKENS);
    if (!commands[k])
        return NULL;

    while (tokens[i])
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            commands[k][j] = NULL;
            k++;
            j = 0;
            commands[k] = malloc(sizeof(char *) * MAX_TOKENS);
            if (!commands[k])
                return NULL;
        }
        else
        {
            commands[k][j++] = strdup(tokens[i]);
        }
        i++;
    }

    commands[k][j] = NULL;
    *cmd_count = k + 1;
    return commands;
}

#define MAX_ARGS 64
#define MAX_REDIRECTS 1024

t_cmd *parse_tokens(char **tokens)
{
    t_cmd *cmd = calloc(1, sizeof(t_cmd));
    if (!cmd)
        return NULL;

    cmd->args = malloc(sizeof(char *) * MAX_ARGS);
    cmd->outfiles = malloc(sizeof(char *) * MAX_REDIRECTS);
    cmd->append_flags = malloc(sizeof(int) * MAX_REDIRECTS);

    int i = 0, j = 0;
    while (tokens[i])
    {
        if ((strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0) && tokens[i + 1])
        {
            cmd->outfiles[cmd->out_count] = strdup(tokens[i + 1]);
            cmd->append_flags[cmd->out_count] = (strcmp(tokens[i], ">>") == 0);
            cmd->out_count++;
            i += 2;
        }
        else if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
        {
            cmd->infile = strdup(tokens[i + 1]);
            i += 2;
        }
        else
        {
            if (!cmd->cmd)
                cmd->cmd = strdup(tokens[i]);
            cmd->args[j++] = strdup(tokens[i]);
            i++;
        }
    }

    cmd->args[j] = NULL;
    return cmd;
}

void free_cmd(t_cmd *cmd)
{
    if (!cmd)
        return;

    if (cmd->cmd)
        free(cmd->cmd);

    if (cmd->infile)
        free(cmd->infile);

    if (cmd->args)
    {
        for (int i = 0; cmd->args[i]; i++)
            free(cmd->args[i]);
        free(cmd->args);
    }

    for (int o = 0; o < cmd->out_count; o++)
        free(cmd->outfiles[o]);
    free(cmd->outfiles);
    free(cmd->append_flags);

    free(cmd);
}
