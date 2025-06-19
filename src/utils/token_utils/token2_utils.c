/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:26:42 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 09:26:42 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_word_len(const char *s)
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

int	is_double_operator(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (1);
	return (0);
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
