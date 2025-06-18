/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@students.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:52 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/18 15:39:01 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	has_unclosed_quotes(const char *str)
{
	char	quote;

	quote = 0;
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

static char	*malloc_token(int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	token[len] = '\0';
	return (token);
}

static char	*make_operator_token(const char **s, int len)
{
	char	*token;
	int		i;

	token = malloc_token(len);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = **s;
		(*s)++;
		i++;
	}
	return (token);
}

static char	*copy_token(const char *start, int len)
{
	int		i;
	char	*token;

	token = malloc_token(len);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	return (token);
}

static int	quoted_len(const char *s, char quote)
{
	int	len;

	len = 1;
	while (s[len] && s[len] != quote)
		len++;
	if (s[len] == quote)
		len++;
	return (len);
}

static int	get_word_len(const char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != ' ' && s[len] != '|' && s[len] != '<'
		&& s[len] != '>')
	{
		if (s[len] == '"' || s[len] == '\'')
			len += quoted_len(s + len, s[len]);
		else
			len++;
	}
	return (len);
}

static int	is_double_operator(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (1);
	return (0);
}

static int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static char	*get_token(const char **str_ptr)
{
	const char	*s;
	char		*token;
	int			len;

	s = *str_ptr;
	while (*s == ' ')
		s++;
	if (is_operator(*s))
	{
		if (*s == '|')
			len = 1;
		else if (is_double_operator(s))
			len = 2;
		else
			len = 1;
		token = make_operator_token(&s, len);
		*str_ptr = s;
		return (token);
	}
	len = get_word_len(s);
	token = copy_token(s, len);
	*str_ptr = s + len;
	return (token);
}

static char	**allocate_tokens(char *input)
{
	if (!input)
		return (NULL);
	if (has_unclosed_quotes(input))
	{
		write(2, "minishell: syntax error: unclosed quote\n", 40);
		return (NULL);
	}
	return (malloc(sizeof(char *) * (ft_strlen(input) + 1)));
}

static int	fill_tokens_loop(const char *ptr, char **tokens)
{
	int	i;

	i = 0;
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
	return (i);
}

static void	fill_tokens(const char *ptr, char **tokens)
{
	int	count;

	count = fill_tokens_loop(ptr, tokens);
	tokens[count] = NULL;
}

char	**split_input(char *input)
{
	const char	*ptr;
	char		**tokens;

	ptr = input;
	tokens = allocate_tokens(input);
	if (!tokens)
		return (NULL);
	fill_tokens(ptr, tokens);
	return (tokens);
}
