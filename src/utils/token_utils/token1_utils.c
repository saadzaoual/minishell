/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:25:30 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 09:25:30 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

char	*malloc_token(int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	token[len] = '\0';
	return (token);
}

char	*make_operator_token(const char **s, int len)
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

char	*copy_token(const char *start, int len)
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

int	quoted_len(const char *s, char quote)
{
	int	len;

	len = 1;
	while (s[len] && s[len] != quote)
		len++;
	if (s[len] == quote)
		len++;
	return (len);
}
