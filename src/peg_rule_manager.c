#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

PEG	*mk_cap(PEG *rule)
{
	PEG	*res;

	res = mk_peg_rule(CAPTURE);
	res->rule.cap_match.match = match_capture;
	res->rule.cap_match.rule = rule;
	return (res);
}

PEG	*mk_backref(int32_t ith, bool insensitive)
{
	PEG	*res;

	res = mk_peg_rule(BACKREF);
	res->rule.bak_match.ith = ith - (1 * ith < 0);
	res->rule.bak_match.match = &match_backref;
	res->rule.bak_match.ins = insensitive;
	return (res);
}

PEG	*mk_class_match(char *class)
{
	PEG	*res;

	res = mk_peg_rule(STRING);
	res->rule.str_match.match = &match_class;
	*res->rule.str_match.target = make_new_sv(class);
	return (res);
}

PEG	*mk_lit_match(char *str, bool ins)
{
	PEG	*res;

	res = mk_peg_rule(STRING);
	if (ins)
		res->rule.str_match.match = &match_literal_insensitive;
	else
		res->rule.str_match.match = &match_literal;
	*res->rule.str_match.target = make_new_sv(str);
	return (res);
}
