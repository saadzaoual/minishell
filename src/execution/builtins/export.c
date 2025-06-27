/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:38:37 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/20 16:42:09 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*extract_key(char *arg)
{
	char	*key;
	int		len;

	len = ft_strchr(arg, '=') - arg;
	key = ft_substr(arg, 0, len);
	return (key);
}

char	**expand_env(char *arg, char *key, int i)
{
	int		j;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(key);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		new_env[j] = env[j];
		j++;
	}
	new_env[j++] = ft_strdup(arg);
	new_env[j] = NULL;
	j = 0;
	free(env);
	return (new_env);
}

int	update_env_var(char *arg)
{
	int		i;
	size_t	key_len;
	char	*key;

	key = extract_key(arg);
	if (!key)
		return (1);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
		{
			free(env[i]);
			env[i] = ft_strdup(arg);
			free(key);
			return (0);
		}
		i++;
	}
	env = expand_env(arg, key, i);
	free(key);
	return (!env);
}
void	print_exported_env(void)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)

		{
			*equal_sign = '\0'; 
			printf("declare -x %s=\"%s\"\n", env[i], equal_sign + 1);
			*equal_sign = '='; 
		}
		else
		{
			printf("declare -x %s\n", env[i]);
		}
		i++;
	}
}
int	builtin_export(char **args)
{
	int	i;

	i = 1;
	if(!args[1])
		print_exported_env();
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			update_env_var(args[i]);
		else
			printf("export: %s: not valid\n", args[i]);
		i++;
	}
	return (0);
}
