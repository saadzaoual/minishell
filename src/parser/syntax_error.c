/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:56:44 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 11:56:44 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operatorsyserror(const char *s)
{
	return (!ft_strcmp(s, "|")
		|| !ft_strcmp(s, ">")
		|| !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "<<"));
}
int	is_redir(const char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<") || !ft_strcmp(s, "<<"));
}

int	is_pipe(const char *s)
{
	return (!ft_strcmp(s, "|"));
}

int	check_syntax(char **tokens)
{
	int i;

	if (!tokens || !tokens[0])
		return (0);

	i = 0;

	// First token can't be a pipe
	if (is_pipe(tokens[i]))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", tokens[i]);
		return (1);
	}

	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
		{
			if (!tokens[i + 1] || is_pipe(tokens[i + 1]))
			{
				printf("minishell: syntax error near unexpected token `%s'\n", tokens[i]);
				return (1);
			}
		}
		else if (is_redir(tokens[i]))
		{
			if (!tokens[i + 1] || is_operatorsyserror(tokens[i + 1]))
			{
				printf("minishell: syntax error near unexpected token `%s'\n", tokens[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}