/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:33:54 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/28 18:38:39 by rkowalsk         ###   ########lyon.fr   */
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

int	pars_spaces(char **command, t_env **env_list)
{
	int		i;
	char	**line;
	char	status;
	int		save[2];

	i = 0;
	status = 0;
	if (command[1])
		save_fds(save);
	while (command[i])
	{
		if (command[i + 1])
			status++;
		line = split_spaces(command[i]);
		if (!line)
			return (-1);
		status = fork_execute(line, env_list, status);
		if (status < 0 || status == 2)
			return (-1);
		status = 0;
		i++;
	}
	if (i > 1)
		reset_fds(save);
	return (0);
}

void	print_int_tab_tab(int **tab, char **command)
{
	int	i;
	i = 0;
	while (tab[i])
	{
		dprintf(1, "|%s| [%d] [%d]\n", command[i], tab[i][0], tab[i][1]);
		i++;
	}
}

int	pars_pipes(char **commands, t_env **env_list)
{
	int		ret;
	int		i;
	int		**fd_tab;
	char	**command;

	i = 0;
	while (commands[i])
	{
		ret = split_pipes(commands[i], &command);
		if (ret == 0)
			return (error_ret_0("Syntax error"));
		if (ret == -1)
			return (-1);
		dprintf(1, "%d\n", redirection(command, &fd_tab));
		print_int_tab_tab(fd_tab, command);
		if (pars_spaces(command, env_list) < 0)
			return (free_split_ret_error(command));
		free_split(command);
		i++;
	}
	return (0);
}

int	pars_line(char *line, t_env **env_list)
{
	int		ret;
	char	**commands;

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
