/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:50:41 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/07 17:24:00 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	proceed_cmd(char **cmd, t_env **env_list)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (cmd[i] && cmd[i][0] != '=' && ft_strchr(cmd[i], '='))
	{
		if (set_variable(cmd[i], env_list) == -1)
			return (free_split_ret_error(cmd));
		i++;
	}
	if (!cmd[i])
		return (free_split(cmd));
	else if (!ft_strcmp(cmd[i], "env"))
		ret = cmd_env(cmd + i, *env_list);
	else if (!ft_strcmp(cmd[i], "export"))
		ret = cmd_export(cmd + i, *env_list);
	else if (!ft_strcmp(cmd[i], "unset"))
		ret = cmd_unset(cmd + i, env_list);
	else if (!ft_strcmp(cmd[i], "cd"))
		ret = cmd_cd(cmd + i);
	else if (!ft_strcmp(cmd[i], "pwd"))
		ret = cmd_pwd(cmd + i);
	else if (!ft_strcmp(cmd[i], "echo"))
		ret = cmd_echo(cmd + i);
	else
		cmd_execve(cmd + i, *env_list);
	free_split(cmd);
	return (ret);
}
