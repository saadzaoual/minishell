/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer1_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:18:00 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 09:18:00 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	realloc_args(char ***args, int *cap, int used)
{
	char	**new_args;
	int		k;

	k = 0;
	*cap *= 2;
	new_args = malloc(sizeof(char *) * (*cap));
	while (k < used)
	{
		new_args[k] = (*args)[k];
		k++;
	}
	free(*args);
	*args = new_args;
}

void	handle_argument(t_cmd *cmd, char **tokens, t_arginfo *info)
{
	if (info->j >= info->cap)
		realloc_args(&cmd->args, &info->cap, info->j);
	if (!cmd->cmd)
		cmd->cmd = ft_strdup(tokens[info->i]);
	cmd->args[info->j++] = ft_strdup(tokens[info->i]);
	info->i++;
}

void	handle_redir(t_cmd *cmd, char **tokens, int *i)
{
	t_rtype	type;

	if (tokens[*i][0] == '<')
		type = R_IN;
	else if (tokens[*i][1] == '>')
		type = R_APPEND;
	else
		type = R_OUT;
	add_redir(cmd, create_redir(type, tokens[*i + 1]));
	*i += 2;
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	t_redir	*r;
	t_redir	*next;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		r = cmd->redirs;
		while (r)
		{
			next = r->next;
			free(r->file);
			free(r);
			r = next;
		}
		free(cmd);
		cmd = tmp;
	}
}
