/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:58:26 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/03 19:46:46 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include "get_next_line.h"
# define MCK(s, r)if((s) == NULL)return(r)

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *str);
void				ft_putnbr(intmax_t nb);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
char				*ft_strcpy(char *dst, const char *src);
void				ft_putstr(char const *str);
void				ft_putallstrs(char **strs);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				*ft_strdup(const char *s1);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isspace(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_pow(int x, int y);
int					ft_atoi(const char *str);
double				ft_abs_val(double x);
int					ft_max_val(int x, int y);
int					ft_min_val(int x, int y);
int					err_ret(char *str);
char				*ft_itoa(int n);
void				ft_swap(int *a, int *b);
void				*ft_memset(void *b, int c, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strstr(const char *haystack, const char *needle);
void				ft_bzero(void *s, size_t n);
int					ft_digit(int c);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_a_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
int					ft_strsubcpy(char *source, char *dst, int len, int start);
int					ft_strdmpnfree(char *source, char *dst, int len, int start);
int					ft_putc_in_str(char *source, char c, int len, int start);
char				*ft_strncpy(char *dst, const char *src, size_t n);
void				ft_strdel(char **as);
void				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
void				ft_strrev(char *str);
char				**ft_strsplit(char const *s, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swap(int *a, int *b);
int					ft_digit(int n);
int					ft_countwords(const char *str, char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					get_next_line(int fd, char **line);

#endif
