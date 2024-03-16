/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:22:13 by iganiev           #+#    #+#             */
/*   Updated: 2024/01/05 10:35:40 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export	*get_export(t_env *env)
{
	t_export	*export_data;
	t_keymap	*current;

	export_data = (t_export *)malloc(sizeof(t_export));
	if (export_data == NULL)
		return (perror("Memory allocation error"), NULL);
	export_data->keymap = NULL;
	current = env->keymap;
	while (current != NULL)
	{
		add_env(&(export_data->keymap), current->key, current->val);
		current = current->next;
	}
	return (export_data);
}

void	export_arg(t_env *env, t_export *export, char *arg)
{
	char	*equals;
	char	*key;
	char	*val;

	equals = ft_strchr(arg, '=');
	key = arg;
	if (equals != NULL && verify_key(arg))
	{
		*equals = '\0';
		val = equals + 1;
		update_or_add_keymap(&(env->keymap), key, val);
		update_or_add_keymap(&(export->keymap), key, val);
		*equals = '=';
	}
	else
		add_env(&(export->keymap), key, NULL);
}

void	ft_export(t_env *env, t_export *export, char **argv)
{
	int	i;

	i = 1;
	if (argv[i] == NULL)
	{
		sort_export(export->keymap);
		print_export(export->keymap);
	}
	else
	{
		while (argv[i] != NULL)
		{
			export_arg(env, export, argv[i]);
			i++;
		}
	}
}
