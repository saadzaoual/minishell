/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:52 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 09:24:23 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*create_redir(t_rtype type, const char *file)
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

void	add_redir(t_cmd *cmd, t_redir *redir)
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

void	append_cmd_node(t_cmd **head, t_cmd **tail, t_cmd *new_node)
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
