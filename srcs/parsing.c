/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:26:50 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/16 11:57:45 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_whitespace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_redirec(char c)
{
	return (c == '>' || c == '<');
}

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
	return (arg);
}

t_token	ft_redirection(char *str, char c, int *i)
{
	t_token	token;

	if (str[*i + 1] && (ft_redirec(str[*i + 1]))) // On regarde si on a un << ou un >> ou un <> ou un ><
	{
		token.value = ft_strndup(str + *i, 2); //On copie a partir de *i 2 cacartere
		if (c != str[*i + 1]) // un <> ou un ><
			token.type = "ERROR";
		else
			token.type = "REDIRECTION";
		*i = *i + 2;
	}
	else // Si c'est un seul caractere on le renvoie ce token
	{
		token.value = malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = "REDIRECTION";
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
		token.type = "ERROR"; // || est dans les bonus donc erreur de syntax
		*i = *i + 2;
	}
	else // Si c'est un seul caractere on le renvoie ce token
	{
		token.value = malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = "PIPE";
		(*i)++;
	}
	return (token);
}

t_token	ft_getarg(char *str, int *i) // On va traiter un argument et voir comment le traiter
{
	t_token	token; // A mon avis un token sera mieux
	char	*s;

	token.value = ft_calloc(sizeof(char), 1);
	s = ft_calloc(sizeof(char), 2);
	while (str[*i] && !ft_whitespace(str[*i])) // Temps que ya pas de whitespace
	{
		if (ft_quote(str[*i])) // Si on tombe sur une quote alors on la parser correctement ducoup ici ca sera forcement un CHAR ARGUMENT de type CHAR *
		{
			(*i)++;
			token.type = "CHAR";
			token.value = free_add_assign(token.value, ft_strjoin(token.value,
						ft_getquote(str, i, str[*i - 1]))); // Et on va la mettre dans token.value avec strjoin
		}
		else // Sinon c un argument classique IL FAUT REGATDER SI YA DES PIPES OU DES TRUCS CHELOU
		{
			if (str[*i] == '\\') // Pour par exemple si on a :  bonsoir je m\'appelle mouloud 
				(*i)++;
			else if (ft_redirec(str[*i]))
			{
				if (ft_strlen(token.value) >= 1)
					return (token);
				else
					return (ft_redirection(str, str[*i], i)); // On capture le < ou le > << >>
			}
			else if (str[*i] == '|')
			{
				if (ft_strlen(token.value) >= 1)
					return (token);
				else
					return (ft_pipe(str, str[*i], i)); // On capture le | ou le ||
			}
			s[0] = str[*i]; // Pour le strjoin
			token.type = "CHAR";
			token.value = free_add_assign(token.value, ft_strjoin(token.value, s)); // Ducoup on va join chaque charactère
		}
		(*i)++;
	}
	return (token);
}

t_token	*ft_partsing(char *str) // La base en gros on va juste récupérér la commande de base et après le parsing va faire le reste
{
	int		i;
	int		j;
	t_token	*cmd;
	t_token	temp;

	cmd = malloc(sizeof(t_token) * 10);
	i = 0;
	while (str[i] && !ft_whitespace(str[i]))  // On va au whitespace
		i++;
	cmd[0].value = ft_strndup(str, i); // On recup la 1er commande
	cmd[0].type = "CMD";
	while (str[i] && ft_whitespace(str[i]))  // On va au prochain argument
		i++;
	j = 1;
	while (str[i])
	{
		temp = ft_getarg(str, &i); // On va recup chaque argument
		if (temp.value)
		{
			// Il faut realloc MOULOUD OUBLIE PAS
			if (ft_strcmp(cmd[j - 1].type, "PIPE") == 0) //SI on avait un pipe le prochain truc est une commande on un prog
				temp.type = "CMD";
			cmd[j++] = temp;
			ft_printf("%d : %s : %s\n", j - 1, cmd[j - 1].type, cmd[j - 1].value);
		}
		if (ft_whitespace(str[i])) // On évite les boucles infini
			i++;
	}
	return (cmd);
}

/*

char	**ft_partsing(char *str)
{
	int		i;
	int		j;
	char	**cmd;
	char	*temp;

	cmd = malloc(sizeof(char *) * 2);
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	cmd[0] = ft_strndup(str, i);
	cmd[1] = NULL;
	while (str[i] && ft_whitespace(str[i]))
		i++;
	j = 1;
	while (str[i])
	{
		temp = ft_getarg(str, &i);
		if (temp)
		{
			cmd = ft_realloc(cmd, sizeof(char *) * (j + 1));
			cmd[j++] = temp;
			//cmd[j + 1] = NULL;
			ft_printf("%d : %s\n", j - 1, cmd[j - 1]);
		}
		i++;
	}
	return (cmd);
}
*/