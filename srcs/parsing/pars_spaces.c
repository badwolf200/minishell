/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:41:34 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/19 14:35:26 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_spaces(char *line)
{
	int		i;
	int		nb_args;

	i = 0;
	nb_args = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == ' ' && (line[i - 1] != ' ' || i == 0))
			nb_args++;
		else if (line[i] == '\'' || line[i] == '\"')
			i = ft_strchr((line + i + 1), line[i]) - line;
		i++;
	}
	if (line[i - 1] != ' ')
		nb_args++;
	return (nb_args);
}

char	*dup_next_word(char *l, int *i)
{
	int		j;
	int		i_save;
	char	*new;

	j = 0;
	i_save = *i;
	while (l[*i] && (l[*i] != ' ' || is_inside_quotes(l, *i)))
	{
		if ((l[*i] != '\"' && l[*i] != '\'') || is_inside_quotes(l, *i))
			j++;
		(*i)++;
	}
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (l[i_save] && (l[i_save] != ' ' || is_inside_quotes(l, i_save)))
	{
		if ((l[i_save] != '\"' && l[i_save] != '\'')
			|| is_inside_quotes(l, i_save))
			new[j++] = l[i_save];
		i_save++;
	}
	new[j] = '\0';
	return (new);
}

char	**split_spaces(char *line)
{
	int		i;
	int		nb_words;
	char	**strs;
	int		j;

	nb_words = get_nb_spaces(line);
	strs = malloc(sizeof(char *) * (nb_words + 1));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && j < nb_words)
	{
		while (line[i] == ' ')
			i++;
		strs[j] = dup_next_word(line, &i);
		if (!strs[j++])
			free_split_ret_error(strs);
		i++;
	}
	strs[j] = NULL;
	return (strs);
}
