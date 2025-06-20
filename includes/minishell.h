/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:00 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/19 19:03:44 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../src/execution/execution.h"

extern char	**env;

typedef enum e_rtype
{
	R_IN,
	R_OUT,
	R_APPEND
}	t_rtype;

typedef struct s_redir
{
	t_rtype			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_arginfo
{
	int	i;
	int	j;
	int	cap;
}	t_arginfo;

char	**split_input(char *input);
t_cmd	*parse_pipeline(char **tokens);
void	free_cmd_list(t_cmd *cmd);

#endif
