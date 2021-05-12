/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_pwd_echo_cd_setvar.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:17:12 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/06 17:35:21 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(char **cmd)
{
	if (cmd[1] && cmd[2])
		ft_printf("Error : too many arguments\n");
	else if (cmd[1])
		chdir(cmd[1]);
	else
		chdir(getenv("HOME"));
	if (errno == 2)
	{
		errno = 0;
		write(1, "Where ?\n", ft_strlen("Where ?\n"));
	}
	return (0);
}

int	cmd_echo(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && !ft_strcmp(cmd[i], "-n"))
		i++;
	while (cmd[i])
	{
		if (i > 1 && ft_strcmp(cmd[i - 1], "-n"))
			write(1, " ", 1);
		ft_printf("%s", cmd[i++]);
	}
	if (!cmd[1] || ft_strcmp(cmd[1], "-n"))
		write(1, "\n", 1);
	return (0);
}

int	cmd_pwd(char **cmd)
{
	char	*path;

	path = NULL;
	if (cmd[1])
		return (error_ret_0("Error : too many arguments"));
	path = getcwd(path, 0);
	if (!path)
		return (-1);
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

int	cmd_env(char **cmd, t_env *env_list)
{
	int	i;

	i = 0;
	if (cmd[1])
		return (error_ret_0("Error : too many arguments"));
	print_list_visible_only(env_list);
	return (0);
}

int	set_variable(char *command, t_env **list)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (command[i] != '=')
		i++;
	command[i++] = '\0';
	value = ft_strdup(command + i);
	name = ft_strdup(command);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (-1);
	}
	if (env_change_value(name, value, *list))
		free(name);
	else
		*list = env_add_link(name, value, false, *list);
	return (0);
}
