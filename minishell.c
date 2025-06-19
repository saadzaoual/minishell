/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:21 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 11:57:00 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

const char	*redir_type_str(t_rtype type)
{
	if (type == R_IN)
		return ("input");
	if (type == R_OUT)
		return ("output");
	return ("append");
}
void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
int	main(void)
{
	char	*input;
	char	**tokens;
	t_cmd	*cmd;
	t_cmd	*head;
	t_redir	*r;
	int		i;
	int		j;
	int		k;

	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = split_input(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		if (check_syntax(tokens))
		{
			free_tokens(tokens);
			free(input);
			continue;
		}
		head = parse_pipeline(tokens);
		cmd = head;
		i = 0;
		while (cmd)
		{
			if (cmd->cmd)
				printf("CMD[%d]: %s\n", i, cmd->cmd);
			else
				printf("CMD[%d]: (null)\n", i);
			j = 0;
			while (cmd->args && cmd->args[j])
			{
				printf("Arg[%d]: %s\n", j, cmd->args[j]);
				j++;
			}
			k = 0;
			r = cmd->redirs;
			while (r)
			{
				printf("Redir[%d]: %s (%s)\n", k, r->file, redir_type_str(r->type));
				r = r->next;
				k++;
			}
			cmd = cmd->next;
			i++;
		}
		free_cmd_list(head);
		free_tokens(tokens);
		free(input);
	}
	printf("exit\n");
	return (0);
}