/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@students.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:52 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/18 15:51:53 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <stdlib.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;

	len = 0;
	while (s[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

static t_redir	*create_redir(t_rtype type, const char *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->file = ft_strdup(file);
	node->next = NULL;
	return (node);
}

static void	add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	if (!tmp)
	{
		cmd->redirs = redir;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

static void	realloc_args(char ***args, int *cap, int used)
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

static void	handle_redir(t_cmd *cmd, char **tokens, int *i)
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

static void	handle_argument(t_cmd *cmd, char **tokens, t_arginfo *info)
{
	if (info->j >= info->cap)
		realloc_args(&cmd->args, &info->cap, info->j);
	if (!cmd->cmd)
		cmd->cmd = ft_strdup(tokens[info->i]);
	cmd->args[info->j++] = ft_strdup(tokens[info->i]);
	info->i++;
}

static t_cmd	*create_cmd_node(char **tokens, int start, int end)
{
	t_cmd		*cmd;
	t_arginfo	info;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	info.i = start;
	info.j = 0;
	info.cap = 4;
	cmd->args = malloc(sizeof(char *) * info.cap);
	cmd->cmd = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	while (info.i < end && tokens[info.i])
	{
		if ((ft_strcmp(tokens[info.i], ">") == 0 || ft_strcmp(tokens[info.i],
					">>") == 0 || ft_strcmp(tokens[info.i], "<") == 0)
			&& tokens[info.i + 1])
			handle_redir(cmd, tokens, &info.i);
		else
			handle_argument(cmd, tokens, &info);
	}
	cmd->args[info.j] = NULL;
	return (cmd);
}

static void	append_cmd_node(t_cmd **head, t_cmd **tail, t_cmd *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
}

t_cmd	*parse_pipeline(char **tokens)
{
	int		start;
	int		i;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_node;

	start = 0;
	i = 0;
	head = NULL;
	tail = NULL;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			new_node = create_cmd_node(tokens, start, i);
			append_cmd_node(&head, &tail, new_node);
			start = i + 1;
		}
		i++;
	}
	new_node = create_cmd_node(tokens, start, i);
	append_cmd_node(&head, &tail, new_node);
	return (head);
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
