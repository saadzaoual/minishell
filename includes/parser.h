/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaoual <szaoual@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:41:59 by szaoual           #+#    #+#             */
/*   Updated: 2025/06/13 16:41:59 by szaoual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

typedef enum e_rtype
{
    R_IN,
    R_OUT,
    R_APPEND
}   t_rtype;

typedef struct s_redir
{
    t_rtype         type;
    char            *file;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
    t_redir *redirs;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_arginfo
{
	int i;
	int j;
	int cap;
}	t_arginfo;

char        **split_input(char *input);
t_cmd       *parse_pipeline(char **tokens);
void        free_cmd_list(t_cmd *cmd);

#endif
