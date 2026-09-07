#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

void	skip_spc(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

char	*push_char(char *s, char c)
{
	char	*res;
	
	res = ft_recalloc(s, LEN(s), LEN(s) + 2, sizeof(char));
	res[LEN(res)] = c;
	return (res);
}
