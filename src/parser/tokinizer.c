/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:41:51 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/13 16:41:51 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static bool is_operator(char c)
{
    return (c == '>' || c == '<' || c == '|');
}

int has_unclosed_quotes(const char *str)
{
    char quote = 0;

    while (*str)
    {
        if (!quote && (*str == '\'' || *str == '"'))
            quote = *str;
        else if (quote && *str == quote)
            quote = 0;
        str++;
    }
    return (quote != 0);
}

static char *get_token(const char **str_ptr)
{
    const char *s = *str_ptr;
    char *token;
    int len = 0;
    char quote = 0;

    while (*s == ' ')
        s++;

    // Handle operators
    if (is_operator(*s))
    {
        if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
            len = 2;
        else
            len = 1;

        token = malloc(len + 1);
        if (!token)
            return NULL;
        strncpy(token, s, len);
        token[len] = '\0';
        *str_ptr = s + len;
        return token;
    }

    // Handle quoted strings
    if (*s == '\'' || *s == '"')
    {
        quote = *s++;
        const char *start = s;
        while (*s && *s != quote)
        {
            s++;
            len++;
        }

        token = malloc(len + 3); // +2 for quotes, +1 for \0
        if (!token)
            return NULL;
        token[0] = quote;
        strncpy(token + 1, start, len);
        token[len + 1] = quote;
        token[len + 2] = '\0';

        if (*s == quote)
            s++; // skip closing quote

        *str_ptr = s;
        return token;
    }

    // Handle normal words
    const char *start = s;
    while (*s && *s != ' ' && !is_operator(*s))
    {
        s++;
        len++;
    }

    token = malloc(len + 1);
    if (!token)
        return NULL;
    strncpy(token, start, len);
    token[len] = '\0';

    *str_ptr = s;
    return token;
}

char **split_input(char *input)
{
    if (!input)
        return NULL;

    if (has_unclosed_quotes(input))
    {
        fprintf(stderr, "minishell: syntax error: unclosed quote\n");
        return NULL;
    }

    int max_tokens = strlen(input); // worst case: one char per token
    char **tokens = malloc(sizeof(char *) * (max_tokens + 1));
    if (!tokens)
        return NULL;

    const char *ptr = input;
    int i = 0;

    while (*ptr)
    {
        while (*ptr == ' ')
            ptr++;
        if (*ptr)
        {
            tokens[i] = get_token(&ptr);
            if (!tokens[i])
                break;
            i++;
        }
    }

    tokens[i] = NULL;
    return tokens;
}
