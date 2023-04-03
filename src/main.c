/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:10:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/03 13:36:27 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex_data	*pipex;
	int				id;
	int				status;

	if (argc < 5)
		error(1, "not enough arguments");
	pipex = init_pipex(argc, argv, envp);
	id = pipe_loop(pipex);
	free(pipex);
	waitpid(id, &status, 0);
	while (wait(NULL) != -1)
		;
	if (!WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

t_pipex_data	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex_data	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex_data));
	if (!pipex)
		error(errno, "malloc erorr");
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_counter = 2;
	pipex->outfile = argv[argc - 1];
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		init_here_doc(pipex, argv);
	else
	{
		pipex->infile = argv[1];
		pipex->infile_fd = open(argv[1], O_RDONLY);
		if (pipex->infile_fd == -1)
			ft_putstr_fd("invalid infile", STDERR_FILENO);
	}
	return (pipex);
}
