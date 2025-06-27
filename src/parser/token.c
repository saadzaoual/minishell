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

#include "../includes/minishell.h"

char	*get_token(const char **str_ptr)
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

char	**allocate_tokens(char *input)
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

int	fill_tokens_loop(const char *ptr, char **tokens)
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

void	fill_tokens(const char *ptr, char **tokens)
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
