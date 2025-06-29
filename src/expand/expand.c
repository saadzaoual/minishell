/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:11:44 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/29 11:11:44 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_value(const char *name)
{
	int		i;
	size_t	len;

	if (!name || !*name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_var_name(const char *str, int *len)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && is_var_char(str[i]))
		i++;
	*len = i;
	res = ft_substr(str, 0, i);
	return (res);
}

static char	*merge_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static char	*replace_var(const char *str, int *i)
{
	char	*name;
	char	*val;
	char	*res;
	int		len;

	if (str[*i + 1] == '$') // check for $$
	{
		*i += 2;
		return (ft_itoa(getpid()));
	}
	(*i)++;
	name = get_var_name(str + *i, &len);
	*i += len;
	val = get_env_value(name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	res = ft_strdup(val);
	return (res);
}


static char	*expand_loop(const char *str, int i, int sq, int quoted)
{
	char	*res;
	char	*tmp;
	char	*rep;
	char	buf[2];

	res = malloc(1);
	res[0] = '\0';
	while (str[i])
	{
		if (str[i] == '\'' && !quoted)
		{
			sq = !sq;
			i++;
		}
		else if (str[i] == '"' && !sq)
		{
			quoted = !quoted;
			i++;
		}
		else if (str[i] == '$' && !sq)
		{
			rep = replace_var(str, &i);
			res = merge_and_free(res, rep);
		}
		else
		{
			buf[0] = str[i++];
			buf[1] = '\0';
			tmp = ft_strdup(buf);
			res = merge_and_free(res, tmp);
		}
	}
	return (res);
}

static char	*expand_word(const char *str)
{
	int		i;
	int		sq;
	int		quoted;

	i = 0;
	sq = 0;
	quoted = 0;
	return (expand_loop(str, i, sq, quoted));
}

void	expand_tokens(char **tokens)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i])
	{
		expanded = expand_word(tokens[i]);
		free(tokens[i]);
		tokens[i] = expanded;
		i++;
	}
}
