#include "../includes/parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int ft_strlen(const char *s)
{
    int i = 0;
    while (s && s[i])
        i++;
    return i;
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

static char *malloc_token(int len)
{
    char *token = malloc(len + 1);
    if (!token)
        return NULL;
    token[len] = '\0';
    return token;
}

static char *make_operator_token(const char **s, int len)
{
    char *token = malloc_token(len);
    int i = 0;
    while (i < len)
    {
        token[i] = **s;
        (*s)++;
        i++;
    }
    return token;
}

static char *copy_token(const char *start, int len)
{
    int i = 0;
    char *token = malloc_token(len);
    if (!token)
        return NULL;
    while (i < len)
    {
        token[i] = start[i];
        i++;
    }
    return token;
}

static int quoted_len(const char *s, char quote)
{
    int len = 1;
    while (s[len] && s[len] != quote)
        len++;
    if (s[len] == quote)
        len++;
    return len;
}

static int get_word_len(const char *s)
{
    int len = 0;
    while (s[len] && s[len] != ' ' && s[len] != '|' && s[len] != '<' && s[len] != '>')
    {
        if (s[len] == '"' || s[len] == '\'')
            len += quoted_len(s + len, s[len]);
        else
            len++;
    }
    return len;
}

static char *get_token(const char **str_ptr)
{
    const char *s = *str_ptr;
    char *token;
    int len;

    while (*s == ' ')
        s++;
    if (*s == '>' || *s == '<')
    {
        len = (s[1] == *s) ? 2 : 1;
        token = make_operator_token(&s, len);
        *str_ptr = s;
        return token;
    }
    if (*s == '|')
    {
        token = make_operator_token(&s, 1);
        *str_ptr = s;
        return token;
    }
    len = get_word_len(s);
    token = copy_token(s, len);
    *str_ptr = s + len;
    return token;
}

static char **allocate_tokens(char *input)
{
    if (!input)
        return NULL;
    if (has_unclosed_quotes(input))
    {
        write(2, "minishell: syntax error: unclosed quote\n", 40);
        return NULL;
    }
    return malloc(sizeof(char *) * (ft_strlen(input) + 1));
}

static int fill_tokens_loop(const char *ptr, char **tokens)
{
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
    return i;
}

static void fill_tokens(const char *ptr, char **tokens)
{
    int count = fill_tokens_loop(ptr, tokens);
    tokens[count] = NULL;
}

char **split_input(char *input)
{
    const char *ptr = input;
    char **tokens = allocate_tokens(input);
    if (!tokens)
        return NULL;
    fill_tokens(ptr, tokens);
    return tokens;
}
