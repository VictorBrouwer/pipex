/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:12:07 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/03 13:48:42 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 0
# define WRITE 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"

typedef struct s_pipex_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*infile;
	int		infile_fd;
	char	*curr_cmd;
	int		cmd_counter;
	int		heredoc;
	char	*hd_delim;
	char	*outfile;
	int		outfile_fd;
	int		read_fd;
}				t_pipex_data;

t_pipex_data	*init_pipex(int argc, char **argv, char **envp);
void			error(int num, char *s);
int				fork_and_check(void);
int				create_pipe(t_pipex_data *pipex);
char			*find_path(char **envp);
char			*get_command_path(t_pipex_data *pipex, char *command);
void			clean_up_split(char **str_arr);
void			redirect_std_in(int fd);
void			redirect_std_out(int fd);
int				pipe_loop(t_pipex_data *pipex);
void			execute_child(t_pipex_data *pipex, int pipefd[2]);
void			execute_last_child(t_pipex_data *pipex, int pipefd[2]);
void			execute_first_child(t_pipex_data *pipex, int pipefd[2]);
void			init_here_doc(t_pipex_data *pipex, char **argv);
void			handle_hd(t_pipex_data *pipex);
char			**pipex_split(char *s, char c);
int				skip_quotes(char const *s, int i);

#endif