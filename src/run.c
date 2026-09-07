#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

intmax_t	eval(PEG *self, t_string_view *str, char **matches, t_act a)
{
	if (self->type == SEQ)
		return (self->rule.chc_match.match(self, str, matches, a));
	else if (self->type == CHOICHE)
		return (self->rule.chc_match.match(self, str, matches, a));
	else if (self->type == GROUP)
		return (self->rule.cap_match.match(self, str, matches, a));
	else if (self->type == LOOKUP)
		return (self->rule.lkp_match.match(self, str, matches, a));
	else if (self->type == CAPTURE)
		return (self->rule.cap_match.match(self, str, matches, a));
	else if (self->type == BACKREF)
		return (self->rule.bak_match.match(self, str, matches, a));
	else if (self->type == ANCHOR)
		return ((self->rule.nch_match.pos == START && !*str->string) - 1);
	else if (self->type == DOT)
		return (self->rule.dot_match.match(self, str, a));
	else if (self->type == STRING)
		return (self->rule.str_match.match(self, str, a));
	else if (self->type == MAYBE)
		return (self->rule.may_match.match(self, str, matches, a));
	return (-1);
}
