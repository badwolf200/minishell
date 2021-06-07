/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:49:21 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/01 15:55:13 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_end(char *var_start)
{
	int	i;

	i = 1;
	while (var_start[i] && (ft_isalnum(var_start[i]) || var_start[i] == '_'
			|| var_start[i] == '?'))
		i++;
	return (i);
}

int	cpy_replace_var(char **line, char *var_start, int var_end, t_env *list)
{
	char	*content;
	char	*new_arg;
	char	*tmp;
	int		size;

	tmp = malloc(sizeof(char) * (var_end + 1));
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, var_start + 1, var_end);
	content = env_get_value(tmp, list);
	free(tmp);
	var_start[0] = '\0';
	if (!content)
		tmp = ft_strjoin(*line, "");
	else
		tmp = ft_strjoin(*line, content);
	if (!tmp)
		return (-1);
	size = ft_strlen(tmp);
	new_arg = ft_strjoin(tmp, var_start + var_end);
	free(tmp);
	free(*line);
	*line = new_arg;
	return (size);
}

void	check_quotes_norme(bool *simple_open, bool *double_open, char c)
{
	if (c == '\'' && !(*double_open))
		(*simple_open) = !(*simple_open);
	else if (c == '\"' && !(*simple_open))
		(*double_open) = !(*double_open);
}

char	*replace_vars(char *line, t_env *list)
{
	int		i;
	bool	simple_open;
	bool	double_open;
	int		var_end;

	i = 0;
	simple_open = false;
	double_open = false;
	while (line[i])
	{
		check_quotes_norme(&simple_open, &double_open, line[i]);
		if (line[i] == '$' && !simple_open)
		{
			var_end = get_var_end(line + i);
			i = cpy_replace_var(&line, line + i, var_end, list);
			if (!line || i < 0)
			{
				free(line);
				return (NULL);
			}
		}
		else
			i++;
	}
	return (line);
}
