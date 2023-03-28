/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:21:32 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/03/28 10:34:42 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_here_doc(t_pipex_data *pipex, char **argv)
{
	if (pipex->argc < 6)
		error(1, "not enough arguments");
	pipex->cmd_counter++;
	pipex->hd_delim = argv[2];
	pipex->heredoc = 1;
}

void	handle_hd(t_pipex_data *pipex)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error(1, "pipe error");
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, pipex->hd_delim, \
			ft_strlen(pipex->hd_delim)) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	pipex->heredoc = 0;
	close(pipefd[WRITE]);
	pipex->read_fd = pipefd[READ];
}
