/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@students.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:30:16 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/16 20:59:53 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <stdlib.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
		s1++, s2++;
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

static t_cmd	*create_cmd_node(char **tokens, int start, int end)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		arg_cap;
			t_rtype type;
	char	**new_args;
	int		k;

	cmd = malloc(sizeof(t_cmd));
	i = start;
	j = 0;
	arg_cap = 4;
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * arg_cap);
	cmd->cmd = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	while (i < end && tokens[i])
	{
		if ((ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
				|| ft_strcmp(tokens[i], "<") == 0) && tokens[i + 1])
		{
			if (tokens[i][0] == '<')
				type = R_IN;
			else if (tokens[i][1] == '>')
				type = R_APPEND;
			else
				type = R_OUT;
			add_redir(cmd, create_redir(type, tokens[i + 1]));
			i += 2;
		}
		else
		{
			if (j >= arg_cap)
			{
				arg_cap *= 2;
				new_args = malloc(sizeof(char *) * arg_cap);
				k = 0;
				while (k < j)
				{
					new_args[k] = cmd->args[k];
					k++;
				}
				free(cmd->args);
				cmd->args = new_args;
			}
			if (!cmd->cmd)
				cmd->cmd = ft_strdup(tokens[i]);
			cmd->args[j] = ft_strdup(tokens[i]);
			j++;
			i++;
		}
	}
	cmd->args[j] = NULL;
	return (cmd);
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
			if (!head)
				head = new_node;
			else
				tail->next = new_node;
			tail = new_node;
			start = i + 1;
		}
		i++;
	}
	new_node = create_cmd_node(tokens, start, i);
	if (!head)
		head = new_node;
	else
		tail->next = new_node;
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
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
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
