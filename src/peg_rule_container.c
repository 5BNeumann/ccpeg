#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

PEG	*mk_seq(PEG *rule)
{
	PEG	*res;

	if (tail(rule) == rule)
		return (rule);
	res = mk_peg_rule(SEQ);
	res->rule.chc_match.match = match_seq;
	res->rule.chc_match.rule = rule;
	return (res);
}

PEG	*mk_choiche(PEG *rule)
{
	PEG	*res;

	res = mk_peg_rule(CHOICHE);
	res->rule.chc_match.match = match_choiche;
	res->rule.chc_match.rule = rule;
	return (res);
}

PEG	*mk_lkp(PEG	*rule, t_lookup l)
{
	PEG	*res;

	if (l == NOT)
		return (rule);
	res = mk_peg_rule(LOOKUP);
	res->rule.lkp_match.match = match_lkp;
	res->rule.lkp_match.rule = rule;
	res->rule.lkp_match.ltype = l;
	return (res);
}

PEG	*mk_grp(PEG *rule)
{
	PEG	*res;

	res = mk_peg_rule(GROUP);
	res->rule.cap_match.match = match_group;
	res->rule.cap_match.rule = rule;
	return (res);
}

PEG	*mk_x_or_moar(PEG *tw, char moar_type)
{
	PEG	*res;

	res = mk_peg_rule(MAYBE);
	res->rule.may_match.maybe_rule = tw;
	if (moar_type == '?')
		res->rule.may_match.match = &match_quest;
	else if (moar_type == '*')
		res->rule.may_match.match = &match_aster;
	else if (moar_type == '+')
		res->rule.may_match.match = &match_plus;
	return (res);
}
