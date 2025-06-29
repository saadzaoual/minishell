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

static int	syntax_error_msg(const char *msg)
{
	write(2, "minishell: syntax error near unexpected token `", 46);
	write(2, msg, ft_strlen(msg));
	write(2, "'\n", 2);
	return (1);
}

static int	check_pipe_error(char **tokens, int i)
{
	if (!tokens[i + 1] || is_pipe(tokens[i + 1]))
		return (syntax_error_msg(tokens[i]));
	return (0);
}

static int	check_redir_error(char **tokens, int i)
{
	if (!tokens[i + 1])
		return (syntax_error_msg("newline"));
	if (is_redir(tokens[i + 1]) || is_pipe(tokens[i + 1]))
		return (syntax_error_msg(tokens[i + 1]));
	return (0);
}

int	check_syntax(char **tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return (0);
	i = 0;
	if (is_pipe(tokens[i]))
		return (syntax_error_msg(tokens[i]));
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) && check_pipe_error(tokens, i))
			return (1);
		if (is_redir(tokens[i]) && check_redir_error(tokens, i))
			return (1);
		i++;
	}
	return (0);
}
