/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:12:28 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/28 19:29:20 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**init_tab(char **command)
{
	int	nb;
	int	i;
	int	**tab;

	i = 0;
	nb = 0;
	while (command[nb])
		nb++;
	tab = malloc(sizeof(int *) * (nb + 1));
	if (!tab)
		return (NULL);
	while (i < nb)
	{
		tab[i] = malloc(sizeof(int) * 2);
		if (!tab[i])
		{
			free_split((char **)tab);
			return (NULL);
		}
		tab[i][0] = 0;
		tab[i][1] = 1;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	get_name_size(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] && ((str[i] != ' ' && str[i] != '>' && str[i] != '<')
		|| is_inside_quotes(str, i)))
	{
		if ((str[i] != '\"' && str[i] != '\'') || is_inside_quotes(str, i))
			size++;
		i++;
	}
	return (i);
}

char	*dup_name(char *str, int *i)
{
	char	*new;
	int		j;

	new = malloc(sizeof(char) * (get_name_size(str + *i) + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (str[*i] && ((str[*i] != ' ' && str[*i] != '>' && str[*i] != '<')
		|| is_inside_quotes(str, *i)))
	{
		if ((str[*i] != '\"' && str[*i] != '\'') || is_inside_quotes(str, *i))
			new[j++] = str[*i];
		(*i)++;
	}
	new[j] = '\0';
	return (new);
}

int	goto_start_of_name(char *str, int i)
{
	while (str[i] && str[i] == '>')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	open_fds_out(char *name, int nb_chevrons, int *fd_tab)
{
	if (nb_chevrons == 1)
		fd_tab[1] = open(name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRGRP | S_IROTH);
	else
		fd_tab[1] = open(name, O_WRONLY | O_CREAT | O_APPEND,
			S_IRWXU | S_IRGRP | S_IROTH);
}

int	open_out(char **command, int i, int *fd_tab)
{
	int		nb_chevrons;
	char	*str;

	nb_chevrons = 1;
	command[0][i++] = '\0';
	while (command[0][i] == '>')
	{
		i++;
		nb_chevrons++;
	}
	if (nb_chevrons > 2)
		return (0);
	i = goto_start_of_name(command[0], i);
	str = dup_name(command[0], &i);
	if (!str)
		return (-1);
	open_fds_out(str, nb_chevrons, fd_tab);
	if (fd_tab[1] < 0)
		return (-1);
	free(str);
	str = ft_strjoin(command[0], command[0] + i);
	if (!str)
		return (-1);
	free(command[0]);
	command[0] = str;
	return (1);
}

void	open_fds_in(char *name, int nb_chevrons, int *fd_tab)
{
	if (nb_chevrons == 1)
		fd_tab[0] = open(name, O_WRONLY | O_CREAT,
			S_IRWXU | S_IRGRP | S_IROTH);
	else
		fd_tab[0] = open(name, O_WRONLY | O_CREAT,
			S_IRWXU | S_IRGRP | S_IROTH);
}

int	open_in(char **command, int i, int *fd_tab)
{
	int		nb_chevrons;
	char	*str;

	nb_chevrons = 1;
	command[0][i++] = '\0';
	while (command[0][i] == '<')
	{
		i++;
		nb_chevrons++;
	}
	if (nb_chevrons > 1)
		return (0);
	i = goto_start_of_name(command[0], i);
	str = dup_name(command[0], &i);
	if (!str)
		return (-1);
	open_fds_in(str, nb_chevrons, fd_tab);
	if (fd_tab[0] < 0)
		return (-1);
	free(str);
	str = ft_strjoin(command[0], command[0] + i);
	if (!str)
		return (-1);
	free(command[0]);
	command[0] = str;
	return (1);
}

int	pars_out(char **command, int *fd_tab)
{
	int	i;
	int	ret;

	i = 0;
	while (command[0][i] && (is_inside_quotes(command[0], i)
		|| command[0][i] != '>'))
		i++;
	if ((int)ft_strlen(command[0]) > i)
	{
		ret = open_out(command, i, fd_tab);
		if (ret < 1)
			return (ret);
		return (pars_out(command, fd_tab));
	}
	return (1);
}

int	pars_in(char **command, int *fd_tab)
{
	int	i;
	int	ret;

	i = 0;
	while (command[0][i] && (is_inside_quotes(command[0], i)
		|| command[0][i] != '<'))
		i++;
	if ((int)ft_strlen(command[0]) > i)
	{
		ret = open_in(command, i, fd_tab);
		if (ret < 1)
			return (ret);
		return (pars_in(command, fd_tab));
	}
	return (1);
}

int	redirection(char **command, int ***fd_tab)
{
	int	i;
	int	ret_in;
	int	ret_out;

	i = 0;
	*fd_tab = init_tab(command);
	if (!*fd_tab)
		return (0);
	while (command[i])
	{
		ret_out = pars_out(command + i, (*fd_tab)[i]);
		if (ret_out == -1)
			return (free_split_ret_error((char **)(*fd_tab)));
		ret_in = pars_in(command + i, (*fd_tab)[i]);
		if (ret_in == -1)
			return (free_split_ret_error((char **)(*fd_tab)));
		if (ret_in == 0 || ret_out == 0)
			return (free_split_perror_ret_0((char **)*fd_tab));
		i++;
	}
	return (1);
}
