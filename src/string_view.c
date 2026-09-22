#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

t_string_view	make_new_sv(char *s)
{
	return ((t_string_view){s, strlen(s), s});
}

void	sv_chop_left(t_string_view *s, intmax_t i)
{
	s->string += MIN(i, s->len);
	s->len -= MIN(i, s->len);
}

void	sv_chop_right(t_string_view *s, intmax_t i)
{
	s->len = MIN(s->len - i, 0);
}

void	free_sv(t_string_view *sv)
{
	free(sv->orig);
	free(sv);
}
