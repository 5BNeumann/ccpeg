#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

char	*parse_lit(char **str)
{
	char	quote;
	char	*res;

	quote = *(*str)++;
	res = calloc(1, sizeof(char));
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

	res = calloc(1, sizeof(char));
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
				res = realloc(res, (strlen(res) + 2) * sizeof(char));
				res[strlen(res) + 1] = 0;
				res[strlen(res)] = s;
			}
			continue ;
		}
		res = realloc(res, (strlen(res) + 2) * sizeof(char));
		res[strlen(res) + 1] = 0;
		res[strlen(res)] = **str;
	}
	return (res);
}
