/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:24:11 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/28 17:38:29 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		i++;
	}
	i++;
	while (i <= 0 && str[i] == ' ')
		i--;
	if (i == '|')
		return (1);
	return (0);
}

int	get_nb_pipes(char *line)
{
	int		i;
	int		nb_semicolons;
	bool	open_single;
	bool	open_double;

	i = 0;
	nb_semicolons = 0;
	open_double = false;
	open_single = false;
	while (line[i])
	{
		if (line[i] == '\'' && !open_double)
			open_single = !open_single;
		else if (line[i] == '\"' && !open_single)
			open_double = !open_double;
		else if (line[i] == '|')
			nb_semicolons++;
		i++;
	}
	return (nb_semicolons);
}

char	**fill_split_pipes(char *line, char **strs)
{
	int		i;
	int		j;
	int		previous;

	previous = 0;
	i = 0;
	j = 0;
	while (previous < (int)ft_strlen(line))
	{
		while ((line[i] && (line[i] != '|' || is_inside_quotes(line, i))))
			i++;
		strs[j] = ft_strndup(line + previous, i - previous);
		if (!strs[j])
		{
			free_split(strs);
			return (NULL);
		}
		j++;
		while (line[i] == '|')
			i++;
		previous = i;
	}
	strs[j] = NULL;
	return (strs);
}

int	split_pipes(char *line, char ***commands)
{
	char	**strs;
	int		i;

	if (check_double_pipes(line))
		return (0);
	strs = malloc(sizeof(char *) * (get_nb_pipes(line) + 2));
	if (!strs)
		return (-1);
	strs = fill_split_pipes(line, strs);
	if (!strs)
		return (-1);
	i = 0;
	while (strs[i])
	{
		if (is_str_empty(strs[i]))
		{
			free_split(strs);
			return (0);
		}
		i++;
	}
	*commands = strs;
	return (1);
}
