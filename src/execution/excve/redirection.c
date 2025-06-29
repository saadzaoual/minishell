/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:03:14 by ayoub             #+#    #+#             */
/*   Updated: 2025/06/29 12:49:12 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_heredoc(char *delimiter)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

int	handle_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == R_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == R_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == R_HEREDOC)
			fd = open_heredoc(redir->file);
		else
			fd = -1;
		if (fd < 0)
			return (perror(redir->file), 1);
		if (redir->type == R_IN || redir->type == R_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
