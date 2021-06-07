/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_escape_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:58:45 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/07 18:22:38 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	else if (str[i - 1] == '\\' && !is_escaped(str, i - 1))
		return (1);
	return (0);
}

void	copy_clear_str(char *str, char *new, char c1, char c2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c1 && str[i] != c2)
			new[j++] = str[i++];
		if (str[i] && is_escaped(str, i) && !is_inside_quotes(str, i))
			new[j - 1] = str[i];
		if (str[i])
			i++;
	}
	new[j] = 0;
}

char	*remove_escape_chars(char *str, char c1, char c2)
{
	int		i;
	int		nb;
	char	*new;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if ((str[i] == c1 || str[i] == c2)
			&& is_escaped(str, i) && !is_inside_quotes(str, i))
			nb++;
		i++;
	}
	if (!nb)
		return (str);
	new = malloc(sizeof(char) * (i - nb + 1));
	if (!new)
		return (NULL);
	copy_clear_str(str, new, c1, c2);
	free(str);
	return (new);
}

char	**remove_escape_from_split(char **str, char c1, char c2)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		str[i] = remove_escape_chars(str[i], c1, c2);
		if (!str[i])
		{
			free_split(str);
			return (NULL);
		}
	}
	return (str);
}