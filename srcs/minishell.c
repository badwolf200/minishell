/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:50:04 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/21 17:07:20 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_nice_path(void)
{
	char	*path;
	int		ret;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (-1);
	ft_printf(ANSI_COLOR_BLUE);
	ret = ft_printf("minishell");
	ft_printf(ANSI_COLOR_RESET);
	ret += ft_printf(" \"%s\" ", path);
	ft_printf(ANSI_COLOR_GREEN);
	ret += ft_printf(">> ");
	ft_printf(ANSI_COLOR_RESET);
	free(path);
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	int				ret;
	t_env			*env_list;
	t_history		*histo_list;
	struct termios	saved_attributes;

	(void) argc;
	(void) argv;
	histo_list = NULL;
	set_input_mode(&saved_attributes);
	env_list = create_env_list(env);
	if (init_termcaps())
		return (EXIT_FAILURE);
	// ft_printf("%s", tgetstr("cl", NULL));
	while (666)
	{
		ret = print_nice_path();
		if (ret < 0)
			return (error_ret(NULL, env_list, saved_attributes, histo_list));
		line = get_line(ret, &histo_list);
		if (!line)
			return (error_ret(NULL, env_list, saved_attributes, histo_list));
		if (!ft_strcmp(line, "exit"))
			return (success_ret(ft_strdup(line), env_list, saved_attributes, histo_list));
		if (pars_line (ft_strdup(line), &env_list) == -1)
			return (error_ret(line, env_list, saved_attributes, histo_list));
		// history_print_list(histo_list);
		// env_print_list(env_list);
	}
	return (0);
}
