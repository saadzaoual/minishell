/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:21 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/18 16:15:45 by szaoual          ###   ########.fr       */
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

int	main(void)
{
	char	*input;
	char	**tokens;
	t_redir	*r;

	t_cmd *cmd, *head;
	int i, j, k;
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
		head = parse_pipeline(tokens);
		cmd = head;
		i = 0;
		while (cmd)
		{
			if (cmd->cmd)
				printf("CMD[%d]: %s\n", i, cmd->cmd);
			else
				printf("CMD[%d]: (null)\n", i);
			i++;
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
				printf("Redir[%d]: %s (%s)\n", k, r->file,
					redir_type_str(r->type));
				r = r->next;
				k++;
			}
			cmd = cmd->next;
		}
		free_cmd_list(head);
		j = 0;
		while (tokens[j])
			free(tokens[j++]);
		free(tokens);
		free(input);
	}
	printf("exit\n");
	return (0);
}
