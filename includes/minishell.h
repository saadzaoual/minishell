/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:27:00 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/29 13:42:53 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/******************************************************************************
*                                   HEADERS                                   *
******************************************************************************/
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
/******************************************************************************
*                                    STRUCTS                                  *
******************************************************************************/
extern char **env;
typedef enum e_rtype
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_rtype;

typedef struct s_redir
{
	t_rtype			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
//.	char			**env;//Stored the env information
//	int				exit_code;//For exit status
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
/******************************************************************************
*                                 Functions                                   *
******************************************************************************/
//token.c:
char	**split_input(char *input);
//parcer.c:
t_cmd	*parse_pipeline(char **tokens);
void	free_cmd_list(t_cmd *cmd);
void	add_redir(t_cmd *cmd, t_redir *redir);
t_redir	*create_redir(t_rtype type, const char *file);
//token1_utils:
int		has_unclosed_quotes(const char *str);
char	*make_operator_token(const char **s, int len);
char	*copy_token(const char *start, int len);
int		quoted_len(const char *s, char quote);
//token2_utils:
int		get_word_len(const char *s);
int		is_double_operator(const char *s);
int		is_operator(char c);
//parcer1_utils:
int		ft_strcmp(const char *s1, const char *s2);
void	handle_redir(t_cmd *cmd, char **tokens, int *i);
void	handle_argument(t_cmd *cmd, char **tokens, t_arginfo *info);
//syntax_error:
int		check_syntax(char **tokens);
//syntax_error_utils:
int		is_redir(const char *s);
int		is_pipe(const char *s);
#endif
