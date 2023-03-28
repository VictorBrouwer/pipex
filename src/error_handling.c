/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:22:37 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/03/23 15:26:29 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	error(int num, char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	if (num != 1)
		exit(num);
	exit(EXIT_FAILURE);
}

int	fork_and_check(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error(1, "forking error");
	return (pid);
}

void	clean_up_split(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}
