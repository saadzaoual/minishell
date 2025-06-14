/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:41:59 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/13 16:41:59 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#include <stdio.h>

typedef struct s_cmd
{
    char *cmd;
    char **args;
    char *infile;
    char **outfiles;
    int  *append_flags;
    int  out_count;
} t_cmd;
char ***split_by_pipe(char **tokens, int *cmd_count);
t_cmd *parse_tokens(char **tokens);
void free_cmd(t_cmd *cmd);
char **split_input(char *input);
int has_unclosed_quotes(const char *str);

#endif
