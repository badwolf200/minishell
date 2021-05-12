/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:33:54 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/12 15:42:19 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_ret_error(char *line, char *error, int	ret)
{
	if (error)
		ft_printf("%s\n", error);
	free(line);
	return (ret);
}

int	check_quotes(char *line)
{
	int		i;
	bool	single_open;
	bool	double_open;

	i = 0;
	single_open = false;
	double_open = false;
	while (line[i])
	{
		if (line[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (line[i] == '\"' && !single_open)
			double_open = !double_open;
		i++;
	}
	if (single_open || double_open)
		return (-1);
	return (0);
}

int	pars_spaces(char **command, t_env ** env_list)
{
	int		i;
	char	**line;
	t_pipe	pip;

	i = 0;
	while (command[i])
	{
		if (command[i + 1] && dprintf(1, "test0\n") && pipe_start(&pip) == -1)
			return (-1);
		line = ft_split(command[i], ' ');
		if (!line)
			return (-1);
		if (proceed_cmd(line, env_list) < 0)
			return (-1);
		if (!command[i + 1] && i > 0 && dprintf(1, "test1\n") && pipe_end(pip) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	pars_pipes(char **commands, t_env **env_list)
{
	int		ret;
	int		i;
	char	**command;

	i = 0;
	while (commands[i])
	{
		ret = split_pipes(commands[i], &command);
		if (ret == 0)
			return (error_ret_0("Syntax error"));
		else if (ret == -1)
			return (-1);
		if (pars_spaces(command, env_list) < 0)
			return (free_split_ret_error(commands));
		free_split(command);
		i++;
	}
	return (0);
}

int	pars_line(char *line, t_env **env_list)
{
	int		ret;
	char	**commands;

	line = ft_strdup(line);
	if (!line)
		return (-1);
	if (check_quotes(line))
		return (free_ret_error(line, "Syntax error", 0));
	line = replace_vars(line, *env_list);
	if (!line)
		return (-1);
	commands = split_semicolons(line);
	if (errno)
		return (-1);
	if (!commands)
		return (error_ret_0("Syntax error"));
	ret = pars_pipes(commands, env_list);
	free_split(commands);
	return (ret);
}
