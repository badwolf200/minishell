/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_returns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:40:53 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/05 18:10:15 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_ret_0(char *error)
{
	ft_printf("%s\n", error);
	return (0);
}

int	error_ret(char *str, t_env *env, struct termios saved, t_history *histo)
{
	if (env)
		env_free_list(env);
	if (histo)
		history_free_list(histo);
	free(str);
	reset_input_mode(saved);
	ft_printf("Error : %s\n", strerror(errno));
	return (EXIT_FAILURE);
}

int	success_ret(char *str, t_env *env, struct termios saved, t_history *histo)
{
	if (!str || !ft_strcmp(str, "exit"))
		ft_printf("KTHXBYE\n");
	else
		ft_printf("\nKTHXBYE\n");
	reset_input_mode(saved);
	// dprintf(1, "test1\n");
	free(str);
	if (env)
		env_free_list(env);
	// dprintf(1, "test2\n");
	if (histo)
		history_free_list(histo);
	// dprintf(1, "test3\n");
	return (EXIT_SUCCESS);
}
