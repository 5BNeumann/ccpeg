#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

char	*parse_lit(char **str)
{
	char	quote;
	char	*res;

	quote = *(*str)++;
	res = ft_calloc(1, sizeof(char));
	while (1)
	{
		if (!**str)
		{
			free(res);
			return (NULL);
		}
		if (*(*str)++ == quote)
			break ;
		if (*--*str == '\\')
		{
			if (!*++*str)
			{
				free(res);
				return (NULL);
			}
			res = push_char(res, *(*str)++);
		}
		else
			res = push_char(res, *(*str)++);
	}
	return (res);
}

char	*parse_class(char **str)
{
	char	*res;
	char	s;

	res = ft_calloc(1, sizeof(char));
	while (*++(*str))
	{
		if (**str == ']')
		{
			++*str;
			break ;
		}
		if (*(*str + 1) == '-' && *(*str + 2) != ']')
		{
			s = **str - 1;
			(*str) += 2;
			while (++s != **str + 1)
			{
				res = ft_recalloc(res, LEN(res), LEN(res) + 2, sizeof(char));
				res[LEN(res)] = s;
			}
			continue ;
		}
		res = ft_recalloc(res, LEN(res), LEN(res) + 2, sizeof(char));
		res[LEN(res)] = **str;
	}
	return (res);
}
