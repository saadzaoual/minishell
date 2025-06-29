/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:21 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/29 13:45:21 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
char **env;

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**tokens;
	t_cmd	*cmd, *head;
	int		j;

	(void)ac;
	(void)av;
	env = copy_env(envp);
//	data.exit_code = 0;
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
		while (cmd)
		{
			if (!execute_command(cmd, head, input))
				break ;
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
