/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:42:28 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/04 12:39:28 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char_to_line(char *line, char c, int pos)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(line) + 2));
	if (new)
	{
		i = 0;
		while (i < pos)
		{
			new[i] = line[i];
			i++;
		}
		new[i] = c;
		while (line[i])
		{
			new[i + 1] = line[i];
			i++;
		}
		new[i + 1] = 0;
	}
	free(line);
	return (new);
}

char	*add_char(char *line, int buffer, t_curs_pos *cursor)
{
	line = add_char_to_line(line, buffer, cursor->line_pos);
	cursor->line_pos++;
	ft_printf("%s", tgetstr("im", NULL));
	write(1, &buffer, 1);
	ft_printf("%s", tgetstr("ei", NULL));
	return (line);
}

char	*ret_exit(void)
{
	write(1, "\n", 1);
	return (ft_strdup("exit"));
}

char	*delete_char_from_line(char *line, int pos)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line)));
	if (new_line)
	{
		while (i < pos)
		{
			new_line[i] = line[i];
			i++;
		}
		while (line[i + 1])
		{
			new_line[i] = line[i + 1];
			i++;
		}
		new_line[i] = 0;
	}
	free (line);
	return (new_line);
}

char	*delete_left(char *line, t_curs_pos *cursor)
{
	if (cursor->line_pos > 0)
	{
		line = delete_char_from_line(line, cursor->line_pos - 1);
		if (!line)
			return (line);
		key_left_right(line, ARROW_LEFT, cursor);
		ft_printf("%s", tgetstr("sc", NULL));
		ft_printf("%s", tgetstr("ce", NULL));
		write(1, line + cursor->line_pos, ft_strlen(line + cursor->line_pos));
		ft_printf(" ");
		ft_printf("%s", tgetstr("rc", NULL));
	}
	return (line);
}

char	*delete_right(char *line, t_curs_pos *cursor)
{
	if (cursor->line_pos < ft_strlen(line))
	{
		line = delete_char_from_line(line, cursor->line_pos);
		if (!line)
			return (line);
		ft_printf("%s", tgetstr("sc", NULL));
		write(1, line + cursor->line_pos, ft_strlen(line + cursor->line_pos));
		ft_printf(" ");
		ft_printf("%s", tgetstr("rc", NULL));
	}
	return (line);
}

void	goto_endofline(t_curs_pos *cursor, char *line)
{
	int	size;

	size = ft_strlen(line);
	while ((int)cursor->line_pos < size)
		key_left_right(line, ARROW_RIGHT, cursor);
}

char	*add_line_history(t_history **list, char *line)
{
	*list = history_add_link(*list, line);
	if (!list)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*get_line(int path_size, t_history **history)
{
	int			ret;
	t_curs_pos	cursor;
	t_history	*curr_hist;
	char		*line;
	int			buffer;

	cursor.line_pos = 0;
	cursor.path_size = path_size;
	buffer = 0;
	line = ft_strdup("");
	*history = history_add_link(*history, line);
	if (!*history)
		return (NULL);
	curr_hist = *history;
	while (buffer != '\n')
	{
		if (!line)
			return (NULL);
		buffer = 0;
		ret = read(0, &buffer, 4);
		if (ret < 0)
			return (NULL);
		else if (buffer == DEL_RIGHT)
			line = delete_right(line, &cursor);
		else if (buffer >= 4283163 || buffer == KEY_DLE)
			line = arrow_keys(line, buffer, &cursor, &curr_hist);
		else if (buffer == DEL_LEFT)
			line = delete_left(line, &cursor);
		else if (buffer == CTRL_D)
			return (ret_exit());
		else if (buffer > 31 && buffer < 127 && buffer != '\n')
			line = add_char(line, buffer, &cursor);
		(*history)->line = line;
	}
	goto_endofline(&cursor, line);
	write(1, &buffer, 1);
	if (!ft_strlen(line))
		*history = history_del_first_link(*history);
	return (line);
}
