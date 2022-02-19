/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:26:50 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/19 14:13:57 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getquote(char *str, int *i, char c)
{
	char	*arg;
	char	*s;

	arg = ft_calloc(sizeof(char), 1);
	s = ft_calloc(sizeof(char), 2);
	while (str[*i] && str[*i] != c) // temps quon retombe pas sur la meme quote
	{
		if (str[*i] == '\\' && str[(*i + 1)] != c) // Pour par exemple si on a :  bonsoir je m\'appelle mouloud 
			(*i)++;
		s[0] = str[*i]; // MOn strjoin ne prend pas de char seulement de char *
		arg = free_add_assign(arg, ft_strjoin(arg, s));
		(*i)++;
	}
	free(s);
	return (arg);
}

t_token	ft_redirection(char *str, char c, int *i)
{
	t_token	token;

	if (str[*i + 1] && (ft_redirec(str[*i + 1]))) // On regarde si on a un << ou un >> ou un <> ou un ><
	{
		token.value = ft_strndup(str + *i, 2); //On copie a partir de *i 2 cacartere
		if (c == '>' && str[*i + 1] == '<') // un ><
			token.type = TOKEN_ERROR;
		else
			token.type = TOKEN_REDIRECTION_OTHER; // faire un ft_check redirection
		*i = *i + 2;
	}
	else // Si c'est un seul caractere on le renvoie ce token
	{
		token.value = malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = TOKEN_REDIRECTION_INPUT; // faire un ft_check redirection
		(*i)++;
	}
	return (token);
}

t_token	ft_pipe(char *str, char c, int *i)
{
	t_token	token;

	if (str[*i + 1] && (c == str[*i + 1])) // On regarde si on a un ||
	{
		token.value = ft_strndup(str + *i, 2); //On copie a partir de *i 2 cacartere
		token.type = TOKEN_ERROR; // || est dans les bonus donc erreur de syntax
		*i = *i + 2;
	}
	else // Si c'est un seul caractere on le renvoie ce token
	{
		token.value = malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = TOKEN_PIPE;
		(*i)++;
	}
	return (token);
}

void	*ft_calloc2(size_t count, size_t size)
{
	char	*copy;

	copy = malloc(size * count);
	if (!(copy))
		return (NULL);
	ft_memset(copy, 0, count * size);
	return (copy);
}


t_token	ft_getarg(char *str, int *i) // On va traiter un argument et voir comment le traiter
{
	t_token	token; // A mon avis un token sera mieux
	char	*s;
	char	*temp;

	token.value = ft_calloc2(sizeof(char), 1);
	s = ft_calloc(sizeof(char), 2);
	while (str[*i] && !ft_whitespace(str[*i])) // Temps que ya pas de whitespace
	{
		if (ft_quote(str[*i])) // Si on tombe sur une quote alors on la parser correctement ducoup ici ca sera forcement un CHAR ARGUMENT de type CHAR *
		{
			(*i)++;
			token.type = TOKEN_ARGUMENT;
			temp = ft_getquote(str, i, str[*i - 1]);
			token.value = free_add_assign(token.value, ft_strjoin(token.value, temp)); // Et on va la mettre dans token.value avec strjoin
			free(temp);
		}
		else // Sinon c un argument classique IL FAUT REGATDER SI YA DES PIPES OU DES TRUCS CHELOU
		{
			if (str[*i] == '\\') // Pour par exemple si on a :  bonsoir je m\'appelle mouloud 
				(*i)++;
			else if (ft_redirec(str[*i]))
			{
				if (ft_strlen(token.value) >= 1)
					return (free_and_return(s, token));
				else
					return (free_and_return(token.value, free_and_return(s, ft_redirection(str, str[*i], i)))); // On capture le < ou le > << >>
			}
			else if (str[*i] == '|')
			{
				if (ft_strlen(token.value) >= 1)
					return (free_and_return(s, token));
				else
					return (free_and_return(token.value, free_and_return(s, ft_pipe(str, str[*i], i)))); // On capture le | ou le ||
			}
			s[0] = str[*i]; // Pour le strjoin
			token.type = TOKEN_ARGUMENT;
			token.value = free_add_assign(token.value, ft_strjoin(token.value, s)); // Ducoup on va join chaque charactère
		}
		(*i)++;
	}
	return (free_and_return(s, token));
}

t_token	*ft_partsing(char *str) // La base en gros on va juste récupérér la commande de base et après le parsing va faire le reste
{
	int		i;
	int		j;
	t_token	*cmd;
	t_token	temp;

	cmd = malloc(sizeof(t_token) * 30);
	i = 0;
	while (str[i] && ft_whitespace(str[i]))  // On va au prochain argument
		i++;
	j = 0;
	while (str[i])
	{
		temp = ft_getarg(str, &i); // On va recup chaque argument
		if (temp.value)
		{
			// Il faut realloc MOULOUD OUBLIE PAS
			//if (ft_strcmp(cmd[j - 1].type, "PIPE") == 0) //SI on avait un pipe le prochain truc est une commande on un prog
			//	temp.type = "CMD";
			cmd[j++] = temp;
			ft_printf("%d : %d : %s\n", j - 1, cmd[j - 1].type, cmd[j - 1].value);
		}
		if (ft_whitespace(str[i])) // On évite les boucles infini
			i++;
	}
	cmd[j].type = TOKEN_NULL;
	cmd[j].value = NULL;
	ft_parse_token(cmd);
	return (cmd);
}