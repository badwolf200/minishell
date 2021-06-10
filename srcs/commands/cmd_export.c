/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:30:14 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/10 18:12:14 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unset(char **cmd, t_env **list)
{
	if (!cmd[1] || cmd[2])
		return (error_ret_0("Error : bad arguments number"));
	*list = env_delete_link(*list, cmd[1]);
	return (1);
}

int	cmd_export(char **cmd, t_env *list)
{
	if (!cmd[1] || cmd[2])
		return (error_ret_0("Error : bad arguments number"));
	set_visible(cmd[1], list);
	return (1);
}
