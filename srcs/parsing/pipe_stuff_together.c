/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stuff_together.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:12:10 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/20 17:23:09 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_start(t_pipe *pip)
{
	int	tab[2];

	pip->saved_out = dup(1);
	pip->saved_in = dup(0);
	close(0);
	close(1);
	if (pipe(tab))
		return (-1);
	return (0);
}

int	pipe_end(t_pipe pip)
{
	close(0);
	close(1);
	if (dup2(pip.saved_out, 1) || dup2(pip.saved_in, 0))
		return (-1);
	close(pip.saved_out);
	close(pip.saved_in);
	return (0);
}
