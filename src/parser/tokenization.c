#include "../includes/parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	ft_strlen(const char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	has_unclosed_quotes(const char *str)
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

static char	*get_token(const char **str_ptr)
{
	const char *s = *str_ptr;
	const char *start;
	char *token;
	int len = 0;
	char quote;

	while (*s == ' ')
		s++;
	if (*s == '>' || *s == '<')
	{
		len = (s[1] == *s) ? 2 : 1;
		token = malloc(len + 1);
		if (!token)
			return (NULL);
		token[0] = *s;
		if (len == 2)
			token[1] = *s;
		token[len] = '\0';
		*str_ptr = s + len;
		return (token);
	}
	if (*s == '|')
	{
		token = malloc(2);
		if (!token)
			return (NULL);
		token[0] = '|';
		token[1] = '\0';
		*str_ptr = s + 1;
		return (token);
	}
	start = s;
	while (*s && *s != ' ' && *s != '|' && *s != '<' && *s != '>')
	{
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			while (*s && *s != quote)
				s++;
			if (*s == quote)
				s++;
		}
		else
			s++;
	}
	len = s - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	for (int i = 0; i < len; i++)
		token[i] = start[i];
	token[len] = '\0';
	*str_ptr = s;
	return (token);
}

char	**split_input(char *input)
{
	const char *ptr = input;
	char **tokens;
	int i = 0;

	if (!input)
		return (NULL);
	if (has_unclosed_quotes(input))
	{
		write(2, "minishell: syntax error: unclosed quote\n", 40);
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	if (!tokens)
		return (NULL);
	while (*ptr)
	{
		while (*ptr == ' ')
			ptr++;
		if (*ptr)
		{
			tokens[i] = get_token(&ptr);
			if (!tokens[i])
				break ;
			i++;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}
