/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@students.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:30:16 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/15 18:32:36 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <stdlib.h>
#include <unistd.h>

#define MAX_CMDS 64
#define MAX_TOKENS 256
#define MAX_ARGS 64
#define MAX_REDIRECTS 1024

static int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
        s1++, s2++;
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static char *ft_strdup(const char *s)
{
    int len = 0;
    while (s[len])
        len++;
    char *dup = malloc(len + 1);
    if (!dup)
        return NULL;
    for (int i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

char ***split_by_pipe(char **tokens, int *cmd_count)
{
    char ***cmds = malloc(sizeof(char **) * MAX_CMDS);
    int i = 0, j = 0, k = 0;

    cmds[k] = malloc(sizeof(char *) * MAX_TOKENS);
    if (!cmds[k])
        return NULL;
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "|") == 0)
        {
            cmds[k][j] = NULL;
            cmds[++k] = malloc(sizeof(char *) * MAX_TOKENS);
            j = 0;
        }
        else
            cmds[k][j++] = ft_strdup(tokens[i]);
        i++;
    }
    cmds[k][j] = NULL;
    *cmd_count = k + 1;
    return cmds;
}

t_cmd *parse_tokens(char **tokens)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    int i = 0, j = 0;

    if (!cmd)
        return NULL;
    cmd->cmd = NULL;
    cmd->args = malloc(sizeof(char *) * MAX_ARGS);
    cmd->infile = NULL;
    cmd->outfiles = malloc(sizeof(char *) * MAX_REDIRECTS);
    cmd->append_flags = malloc(sizeof(int) * MAX_REDIRECTS);
    cmd->out_count = 0;

    while (tokens[i])
    {
        if ((ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0) && tokens[i + 1])
        {
            cmd->outfiles[cmd->out_count] = ft_strdup(tokens[i + 1]);
            cmd->append_flags[cmd->out_count++] = (tokens[i][1] == '>');
            i += 2;
        }
        else if (ft_strcmp(tokens[i], "<") == 0 && tokens[i + 1])
        {
            cmd->infile = ft_strdup(tokens[i + 1]);
            i += 2;
        }
        else
        {
            if (!cmd->cmd)
                cmd->cmd = ft_strdup(tokens[i]);
            cmd->args[j++] = ft_strdup(tokens[i++]);
        }
    }
    cmd->args[j] = NULL;
    return cmd;
}

void free_cmd(t_cmd *cmd)
{
    int i;

    if (!cmd)
        return;
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->infile)
        free(cmd->infile);
    if (cmd->args)
    {
        for (i = 0; cmd->args[i]; i++)
            free(cmd->args[i]);
        free(cmd->args);
    }
    for (i = 0; i < cmd->out_count; i++)
        free(cmd->outfiles[i]);
    free(cmd->outfiles);
    free(cmd->append_flags);
    free(cmd);
}
