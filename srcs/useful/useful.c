/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:49:48 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/07 16:31:53 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_inside_quotes(char *line, int j)
{
	int		i;
	bool	open_single;
	bool	open_double;

	i = 0;
	open_double = false;
	open_single = false;
	while (i < j)
	{
		if (line[i] == '\'' && !open_double)
			open_single = !open_single;
		else if (line[i] == '\"' && !open_single)
			open_double = !open_double;
		i++;
	}
	if (line[i] == '\'' && !open_double)
		open_single = false;
	else if (line[i] == '\"' && !open_single)
		open_double = false;
	return (open_double || open_single);
}

void	reset_input_mode(struct termios saved_attributes)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

int	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

int	split_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
