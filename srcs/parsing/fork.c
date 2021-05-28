/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:00:33 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/26 14:08:27 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fds(int *save)
{
	save[0] = dup(0);
	save[1] = dup(1);
}

void	reset_fds(int *save)
{
	dup2(save[0], 0);
	dup2(save[1], 1);
}

void	dup_in_close_new(int *new)
{
	dup2(new[0], 0);
	close(new[0]);
	close(new[1]);
}

int	fork_execute(char **command, t_env **env_list, char status)
{
	int	pid;
	int new[2];
	int save[2];

	save_fds(save);
	if (status && pipe(new) < 0)
		return (free_split_ret_error(command));
	pid = fork();
	if (pid == -1)
		return (free_split_ret_error(command));
	else if (!pid)
	{
		if (status && dup2(new[1], 1) < 0)
			exit(2);
		exit(proceed_cmd(command, env_list));
	}
	wait(&pid);
	if (status)
		dup_in_close_new(new);
	env_change_value("?", ft_itoa(WEXITSTATUS(pid)), *env_list);
	reset_fds(save);
	return (WEXITSTATUS(pid));
}