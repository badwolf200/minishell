/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:26:59 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/21 15:21:25 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_question_mark(t_env *tab)
{
	char	*name;
	char	*value;

	name = ft_strdup("?");
	value = ft_strdup("0");
	if (!name || !value)
	{
		free(name);
		free(value);
		env_free_list(tab);
		return (NULL);
	}
	tab = env_add_link(name, value, false, tab);
	return (tab);
}

t_env	*create_env_list(char **env_tab)
{
	int		i;
	t_env	*env_list;
	char	*equal;

	i = 0;
	env_list = NULL;
	while (env_tab[i])
	{
		equal = ft_strchr(env_tab[i], '=');
		env_list = env_add_link(ft_strndup(env_tab[i], equal - env_tab[i]),
				ft_strdup(equal + 1), true, env_list);
		if (!env_list->name || !env_list->value)
		{
			env_list = env_delete_link(env_list, env_list->name);
			env_free_list(env_list);
			return (NULL);
		}
		i++;
	}
	return (add_question_mark(env_list));
}

void	set_input_mode(struct termios *saved_attributes)
{
	struct termios	new;

	tcgetattr(0, saved_attributes);
	tcgetattr(0, &new);
	new.c_lflag &= ~(ICANON|ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr (0, TCSAFLUSH, &new);
}

int	init_termcaps(void)
{
	char	*term;
	int		ret;

	term = getenv("TERM");
	if (!term)
	{
		ft_printf(ANSI_COLOR_RED "Variable TERM non initialisée\n" 
			ANSI_COLOR_RESET);
		return (-1);
	}
	ret = tgetent(NULL, term);
	if (ret == 1)
		return (0);
	if (ret == -1)
		ft_printf(ANSI_COLOR_RED "BDD inaccessible\n"
			ANSI_COLOR_RESET);
	else if (ret == 0)
		ft_printf(ANSI_COLOR_RED "Terminal inconnu\n"
			ANSI_COLOR_RESET);
	return (-1);
}

// void	init_keys(t_key_set *keys)
// {
// 	keys->arrow_up[0] = 27;
// 	keys->arrow_up[1] = 91;
// 	keys->arrow_up[2] = 65;
// 	keys->arrow_up[3] = 0;
// 	keys->arrow_down[0] = 27;
// 	keys->arrow_down[1] = 91;
// 	keys->arrow_down[2] = 66;
// 	keys->arrow_down[3] = 0;
// 	keys->arrow_left[0] = 27;
// 	keys->arrow_left[1] = 91;
// 	keys->arrow_left[2] = 68;
// 	keys->arrow_left[3] = 0;
// 	keys->arrow_right[0] = 27;
// 	keys->arrow_right[1] = 91;
// 	keys->arrow_right[2] = 67;
// 	keys->arrow_right[3] = 0;
// 	keys->end[0] = 27;
// 	keys->end[1] = 91;
// 	keys->end[2] = 70;
// 	keys->end[3] = 0;
// 	keys->delete[0] = 27;
// 	keys->delete[1] = 97;
// 	keys->delete[2] = 51;
// 	keys->delete[3] = 126;
// 	keys->delete[4] = 0;
// }
