/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_returns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:40:53 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/06/02 16:22:06 by rkowalsk         ###   ########lyon.fr   */
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
	else
		free(str);
	reset_input_mode(saved);
	ft_printf("Error : %s\n", strerror(errno));
	signal(SIGINT, SIG_DFL);
	return (EXIT_FAILURE);
}

int	success_ret(char *str, t_env *env, struct termios saved, t_history *histo)
{
	if (!str || !ft_strcmp(str, "exit"))
		ft_printf("KTHXBYE\n");
	else
		ft_printf("\nKTHXBYE\n");
	reset_input_mode(saved);
	free(str);
	if (env)
		env_free_list(env);
	if (histo)
		history_free_list(histo);
	signal(SIGINT, SIG_DFL);
	return (EXIT_SUCCESS);
}

int	free_ret_error(char *line, char *error, int	ret)
{
	if (error)
		ft_printf("%s\n", error);
	free(line);
	return (ret);
}
