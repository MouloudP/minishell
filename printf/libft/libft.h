/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:28:56 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/12 10:57:40 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin2(char const *s1, char const *s2, char c);

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

int		ft_atoi(const char *nptr);
char	*ft_strchr(const char *s, char c);
char	*ft_strrchr(const char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strcat(char *dst, const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
