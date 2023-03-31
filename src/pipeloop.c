/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:32:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/03/31 12:11:17 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	pipe_loop(t_pipex_data *pipex)
{
	int	pipefd[2];
	int	pid;

	while (pipex->cmd_counter < (pipex->argc - 2))
	{		
		if (pipex->heredoc == 1)
			handle_hd(pipex);
		if (pipe(pipefd) == -1)
			error(1, "pipe error");
		pid = fork_and_check();
		if (pid == 0)
			execute_child(pipex, pipefd);
		pipex->cmd_counter++;
		pipex->read_fd = pipefd[READ];
		if (pipex->cmd_counter != (pipex->argc - 2))
			close(pipefd[WRITE]);
	}
	pid = fork_and_check();
	if (pid == 0)
		execute_last_child(pipex, pipefd);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	return (pid);
}

void	execute_child(t_pipex_data *pipex, int pipefd[2])
{
	char	**argvp;

	if (pipex->cmd_counter == 2)
		execute_first_child(pipex, pipefd);
	close(pipefd[READ]);
	redirect_std_in(pipex->read_fd);
	redirect_std_out(pipefd[WRITE]);
	argvp = ft_split(pipex->argv[pipex->cmd_counter], ' ');
	pipex->curr_cmd = get_command_path(pipex, argvp[0]);
	if (execve(pipex->curr_cmd, argvp, pipex->envp) == -1)
		error(errno, "execve error");
}

void	execute_first_child(t_pipex_data *pipex, int pipefd[2])
{
	char	**argvp;

	close(pipefd[READ]);
	if (pipex->infile_fd != -1)
		redirect_std_in(pipex->infile_fd);
	redirect_std_out(pipefd[WRITE]);
	argvp = ft_split(pipex->argv[pipex->cmd_counter], ' ');
	pipex->curr_cmd = get_command_path(pipex, argvp[0]);
	if (execve(pipex->curr_cmd, argvp, pipex->envp) == -1)
		error(errno, "execve error");
}

void	execute_last_child(t_pipex_data *pipex, int pipefd[2])
{
	char	**argvp;

	close(pipefd[WRITE]);
	redirect_std_in(pipex->read_fd);
	if (ft_strncmp(pipex->argv[1], "here_doc", 8) == 0)
		pipex->outfile_fd = open(pipex->outfile, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		pipex->outfile_fd = open(pipex->outfile, \
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	redirect_std_out(pipex->outfile_fd);
	argvp = ft_split(pipex->argv[pipex->cmd_counter], ' ');
	pipex->curr_cmd = get_command_path(pipex, argvp[0]);
	if (execve(pipex->curr_cmd, argvp, pipex->envp) == -1)
		error(errno, "execve error");
}
