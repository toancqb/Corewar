/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 15:05:10 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 17:14:56 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <wchar.h>
# include "printf.h"

typedef	unsigned char	t_byte;

typedef unsigned long	t_lword;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *s, int c, size_t n);

void			*ft_memcpy(void *dest, const void *src, size_t n);

void			*ft_memccpy(void *dest, const void *src, int c, size_t n);

void			*ft_memmove(void *dest, const void *src, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			ft_bzero(void *s, size_t n);

size_t			ft_strlen(const char *s);

size_t			ft_strnlen(const char *s, size_t maxlen);

size_t			ft_wcharlen(wint_t c);

size_t			ft_wstrlen(wchar_t *str);

char			*ft_strdup(const char *s);

char			*ft_strndup(const char *s, size_t n);

char			*ft_strcpy(char *dest, const char *src);

char			*ft_strncpy(char *dest, const char *src, size_t n);

char			*ft_strcat(char *dest, const char *src);

char			*ft_strncat(char *dest, const char *src, size_t n);

size_t			ft_strlcat(char *dest, const char *src, size_t size);

char			*ft_strchr(const char *s, int c);

char			*ft_strrchr(const char *s, int c);

char			*ft_strstr(const char *haystack, const char *needle);

char			*ft_strnstr(const char *haystack, const char *needle, size_t n);

int				ft_strcmp(const char *s1, const char *s2);

int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				ft_atoi(const char *str);

int				ft_atoi_base(const char *str, int base);

int				ft_simple_atoi(const char **str);

long int		ft_strtol(const char *nptr, char **endptr, int base);

int				ft_isalpha(int c);

int				ft_isdigit(int c);

int				ft_isalnum(int c);

int				ft_isascii(int c);

int				ft_isprint(int c);

int				ft_toupper(int c);

int				ft_tolower(int c);

int				ft_isspace(int c);

int				ft_isupper(int c);

int				ft_islower(int c);

char			*ft_strtoupper(char *s);

char			*ft_strtolower(char *s);

void			*ft_memalloc(size_t size);

void			ft_memdel(void **ap);

char			*ft_strnew(size_t size);

void			ft_strdel(char **as);

void			ft_strclr(char *s);

void			ft_striter(char *s, void (*f)(char *));

void			ft_striteri(char *s, void (*f)(unsigned int, char *));

char			*ft_strmap(char const *s, char (*f)(char));

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_strequ(char const *s1, char const *s2);

int				ft_strnequ(char const *s1, char const *s2, size_t n);

char			*ft_strsub(char const *s, unsigned int start, size_t len);

char			*ft_strjoin(char const *s1, char const *s2);

char			*ft_strjoin_free(char *s1, char const *s2);

char			*ft_strtrim(char const *s);

char			*ft_strstrim(char const *s, char const *spaces);

char			*ft_strreplace(const char *s, const char *from, const char *to);

char			*ft_strreplace_free(char *s, const char *from, const char *to);

char			**ft_strsplit(char const *s, char c);

char			*ft_join(char **tab, const char *glue);

char			*ft_itoa(int n);

char			*ft_itoa_base(int n, int base);

char			*ft_lltoa(long long n);

char			*ft_lltoa_base(long long n, int base);

char			*ft_ulltoa(unsigned long long n);

char			*ft_ulltoa_base(unsigned long long n, int base);

void			ft_putchar(char c);

void			ft_putwchar(int c);

void			ft_putchar_fd(char c, int fd);

void			ft_putstr(char const *s);

void			ft_putstr_fd(char const *s, int fd);

void			ft_putendl(char const *s);

void			ft_putendl_fd(char const *s, int fd);

void			ft_putnbr(int n);

void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);

void			*ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void			*ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void			*ft_lstfree(t_list **alst);

void			ft_lstadd(t_list **alst, t_list *new);

void			ft_lstpush(t_list **alst, t_list *new);

t_list			*ft_lstpop(t_list **alst);

t_list			*ft_lstpeek(t_list *lst);

size_t			ft_lstsize(t_list *lst);

int				ft_lstempty(t_list *lst);

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int				ft_min(int a, int b);

int				ft_max(int a, int b);

int				ft_abs(int n);

int				ft_pow(int n, int pow);

size_t			ft_llsize(long long l);

void			*ft_strtab_free(char **tab);

int				ft_levenshtein(const char *s1, const char *s2);

#endif
