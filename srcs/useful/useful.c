/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:49:48 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/07 17:34:37 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* les quotes de début et de fin ne sont pas inside_quotes */

char	is_inside_quotes(char *line, int j)
{
	int		i;
	bool	open_single;
	bool	open_double;

	i = 0;
	open_double = false;
	open_single = false;
	while (i < j)
	{
		if (line[i] == '\'' && !is_escaped(line, i) && !open_double)
			open_single = !open_single;
		else if (line[i] == '\"' && !is_escaped(line, i) && !open_single)
			open_double = !open_double;
		i++;
	}
	if (line[i] == '\'' && !is_escaped(line, i) && !open_double)
		open_single = false;
	else if (line[i] == '\"' && !is_escaped(line, i) && !open_single)
		open_double = false;
	if (open_double)
		return ('\"');
	if (open_single)
		return ('\'');
	return (0);
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
