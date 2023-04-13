/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:19:59 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/07 15:34:43 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*find_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_command_path(t_pipex_data *pipex, char *command)
{
	char	*path;
	char	**sep_paths;
	char	*end_part_command;
	char	*total_command;
	int		i;

	if (access(command, X_OK & F_OK) == 0)
		return (command);
	path = find_path(pipex->envp);
	if (path == NULL || !command)
		error(1, "command not found");
	sep_paths = ft_split(path, ':');
	end_part_command = ft_strjoin("/", command);
	i = 0;
	while (sep_paths[i] != NULL)
	{
		total_command = ft_strjoin(sep_paths[i], end_part_command);
		if (access(total_command, X_OK & F_OK) == 0)
			return (clean_up_split(sep_paths), total_command);
		i++;
	}
	clean_up_split(sep_paths);
	error(1, "command not found");
	return (NULL);
}
