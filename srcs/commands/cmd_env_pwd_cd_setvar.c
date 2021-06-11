/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_pwd_cd_setvar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:17:12 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/11 18:27:17 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(char **cmd, t_env **list)
{
	if (cmd[1] && cmd[2])
		write(2, "Error : too many arguments\n", 27);
	else if (cmd[1])
	{
		chdir(cmd[1]);
		if (!ft_strcmp("//", cmd[1]))
		{
			env_change_value("PWD", ft_strdup("//"), *list);
		}
		else
			env_change_value("PWD", getcwd(NULL, 0), *list);
	}
	else
	{
		chdir(getenv("HOME"));
		env_change_value("PWD", ft_strdup(getenv("HOME")), *list);
	}
	if (errno == 2)
	{
		errno = 0;
		write(2, "Where ?\n", 8);
	}
	return (0);
}

int	cmd_pwd(char **cmd, t_env *list)
{
	if (cmd[1])
		return (error_ret_0("Error : too many arguments"));
	ft_printf("%s\n", env_get_value("PWD", list));
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
	while (command[i] != '=' || is_escaped(command, i))
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
