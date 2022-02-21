/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:26:50 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/21 13:16:54 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_quote_env(char *str, char c, t_m *mini)
{
	int		i;
	int		start;
	char	*temp;
	char	*copy;
	char	*temp2;

	i = 0;
	while (str[i] && c != '\'')
	{
		if (str[i] == '$')
		{
			start = i + 1;
			i++;
			if (str[i] == '{')
				start = (++i);
			while (str[i] && !ft_whitespace(str[i]) && str[i] != '$' && str[i] != '}')
				i++;
			//ft_printf("END WHILE\n");
			temp = str + start;
			if (str[i] == '}')
			{
				temp = ft_strndup(temp, i - start);
				temp2 = ft_strndup(str, start - 2);
			}
			else
			{
				temp = ft_strndup(temp, i - start);
				temp2 = ft_strndup(str, start - 1);
			}
			//ft_printf("START : |%s|\n", temp2);
			//ft_printf("MILIEU : |%s|\n", temp);
			if (ft_getenv(mini, temp))
				copy = ft_strjoin(temp2, ft_getenv(mini, temp));
			else
				copy = ft_strdup(temp2);
			free(temp);
			free(temp2);
			temp = copy;
			if (str[i] == '}')
				copy = ft_strjoin(copy, str + i + 1);
			else
				copy = ft_strjoin(copy, str + i);
			//ft_printf("END : |%s|\n", str + i);
			//ft_printf("MILIEU : |%s|\n", ft_getenv(mini, temp));
			//ft_printf("FINALE : |%s| \n", copy);
			free(str);
			str = copy;
			str = ft_quote_env(str, c, mini);
			break;
		}
		i++;
	}
	return (str);
}

char	*ft_getquote(char *str, int *i, char c, t_m *mini) // Check env dans les quotes OUBLIE PAS !
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
	arg = ft_quote_env(arg, c, mini);
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

t_token	ft_redirection(char *str, char c, int *i, t_m *mini)
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
			temp = ft_getarg(str, i, mini);
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

t_token	ft_getarg(char *str, int *i, t_m *mini) // On va traiter un argument et voir comment le traiter
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
			temp = ft_getquote(str, i, str[*i - 1], mini);
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
					return (free_and_return(token.value, free_and_return(s, ft_redirection(str, str[*i], i, mini)))); // On capture le < ou le > << >>
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
	//char	*temp;

	i = 0;
	while (cmd[i].type)
	{
		if (cmd[i].env)
		{
			cmd[i].value = ft_quote_env(cmd[i].value, '"', mini);
			if (!cmd[i].value || ft_strlen(cmd[i].value) <= 0)
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
		temp = ft_getarg(str, &i, mini); // On va recup chaque argument
		if (temp.value)
		{
			cmd = ft_realloc_cmd(cmd, j);
			cmd[j++] = temp;
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