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
#include <stdbool.h>

static int count_words(const char *str);
static char *extract_token(const char **str_ptr);

char **split_input(char *input)
{
    int word_count = count_words(input);
    char **result = malloc(sizeof(char *) * (word_count + 1));
    if (!result)
        return NULL;

    int i = 0;
    const char *ptr = input;
    while (*ptr)
    {
        while (*ptr == ' ')
            ptr++;
        if (*ptr)
            result[i++] = extract_token(&ptr);
    }
    result[i] = NULL;
    return result;
}

static int count_words(const char *str)
{
    int count = 0;
    bool in_quote = false;
    char quote_char = 0;

    while (*str)
    {
        while (*str == ' ')
            str++;
        if (*str)
        {
            count++;
            while (*str && (in_quote || (*str != ' ')))
            {
                if (!in_quote && (*str == '\'' || *str == '\"'))
                {
                    in_quote = true;
                    quote_char = *str;
                }
                else if (in_quote && *str == quote_char)
                {
                    in_quote = false;
                }
                str++;
            }
        }
    }
    return count;
}

static char *extract_token(const char **str_ptr)
{
    const char *str = *str_ptr;
    char quote = 0;
    int len = 0;

    while (*str == ' ')
        str++;

    while (*str && (quote || *str != ' '))
    {
        if (!quote && (*str == '\'' || *str == '\"'))
            quote = *str;
        else if (quote && *str == quote)
            quote = 0;
        str++;
        len++;
    }

    char *token = malloc(len + 1);
    if (!token)
        return NULL;

    int j = 0;
    quote = 0;
    while (**str_ptr && (quote || **str_ptr != ' ') && j < len)
    {
        if (!quote && (**str_ptr == '\'' || **str_ptr == '\"'))
            quote = **str_ptr;
        else if (quote && **str_ptr == quote)
            quote = 0;
        else
            token[j++] = **str_ptr;
        (*str_ptr)++;
    }
    token[j] = '\0';
    return token;
}
