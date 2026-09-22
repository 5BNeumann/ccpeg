#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

void	skip_spc(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

char	*push_char(char *s, char c)
{
	char	*res;
	
	res = realloc(s, (strlen(s) + 2) * sizeof(char));
	res[strlen(res) + 1] = 0;
	res[strlen(res)] = c;
	return (res);
}
