/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:02:57 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/03/23 14:27:03 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	redirect_std_in(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		error(1, "duplication std_in error");
	close(fd);
}

void	redirect_std_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		error(1, "duplication std_out error");
	close(fd);
}
