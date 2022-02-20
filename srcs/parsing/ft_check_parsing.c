/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:26:50 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/20 14:59:47 by ahamdoun         ###   ########.fr       */
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

int	ft_get_redirection(char *s)
{
	if (ft_strcmp(s, ">") == 0)
		return (TOKEN_REDIRECTION_INPUT);
	else if (ft_strcmp(s, "<") == 0)
		return (TOKEN_REDIRECTION_OUTPUT);
	else if (ft_strcmp(s, ">>") == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strcmp(s, "<<") == 0)
		return (TOKEN_REDIRECTION_DELIMTER);
	else if (ft_strcmp(s, "<>") == 0)
		return (TOKEN_REDIRECTION_OTHER);
	return (TOKEN_ERROR);
}

t_token	ft_redirection(char *str, char c, int *i)
{
	t_token	token;
	t_token	temp;

	token.env = 0;
	token.type = 0;
	if (str[*i + 1] && (ft_redirec(str[*i + 1]))) // On regarde si on a un << ou un >> ou un <> ou un ><
	{
		token.value = ft_strndup(str + *i, 2); //On copie a partir de *i 2 cacartere
		if (c == '>' && str[*i + 1] == '<') // un ><
			token.type = TOKEN_ERROR;
		else
			token.type = ft_get_redirection(token.value); // faire un ft_check redirection
		*i = *i + 2;
		if (token.type == TOKEN_REDIRECTION_DELIMTER)
		{
			while (str[(*i)] && ft_whitespace(str[(*i)]))
				(*i)++;
			temp = ft_getarg(str, i);
			ft_delimiters(temp.value, &token);
			free(temp.value);
		}
	}
	else // Si c'est un seul caractere on le renvoie ce token
	{
		token.value = malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = ft_get_redirection(token.value); // faire un ft_check redirection
		(*i)++;
	}
	return (token);
}

t_token	ft_pipe(char *str, char c, int *i)
{
	t_token	token;

	token.env = 0;
	token.type = 0;
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

t_token	ft_getarg(char *str, int *i) // On va traiter un argument et voir comment le traiter
{
	t_token	token; // A mon avis un token sera mieux
	char	*s;
	char	*temp;

	token.value = ft_calloc(sizeof(char), 1);
	token.env = 0;
	token.fd = 0;
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
			else if (str[*i] == '$')
				token.env = 1;
			s[0] = str[*i]; // Pour le strjoin
			token.type = TOKEN_ARGUMENT;
			token.value = free_add_assign(token.value, ft_strjoin(token.value, s)); // Ducoup on va join chaque charactère
		}
		(*i)++;
	}
	return (free_and_return(s, token));
}

t_token *ft_parse_env(t_token *cmd, t_m *mini, int j)
{
	int 	i;
	char	*temp;

	i = 0;
	while (cmd[i].type)
	{
		if (cmd[i].env)
		{
			temp = ft_getenv(mini, cmd[i].value + 1);
			if (temp)
			{
				free(cmd[i].value);
				cmd[i].value = ft_strdup(temp);
			}
			else
			{
				cmd = ft_remove_cmd(cmd, j--, i);
				cmd = ft_parse_env(cmd, mini, j);
				break;
			}
		}
		i++;
	}
	return (cmd);
}

t_token	*ft_partsing(char *str, t_m *mini) // La base en gros on va juste récupérér la commande de base et après le parsing va faire le reste
{
	int		i;
	int		j;
	t_token	*cmd;
	t_token	temp;

	cmd = malloc(sizeof(t_token) * 1);
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
			cmd = ft_realloc_cmd(cmd, j);
			cmd[j++] = temp;
			//ft_printf("%d : %d : %s\n", j - 1, cmd[j - 1].type, cmd[j - 1].value);
		}
		while (str[i] && ft_whitespace(str[i])) // On évite les boucles infini
			i++;
	}
	cmd[j].type = TOKEN_NULL;
	cmd[j].value = NULL;
	cmd = ft_parse_env(cmd, mini, j);
	ft_parse_token(cmd, mini);
	return (cmd);
}