#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

intmax_t	match_lkp(PEG *self, SV *str, char **matches, t_act act)
{
	if (self->rule.lkp_match.ltype == NOT)
		return (eval(self->rule.lkp_match.rule, str, matches, act));
	else if (self->rule.lkp_match.ltype == POS)
		return (-(eval(self->rule.lkp_match.rule, str, matches, PEEK) < 0));
	return (-(eval(self->rule.lkp_match.rule, str, matches, PEEK) >= 0));
}

intmax_t	match_plus(t_peg_rule *rule, SV *str, char **matches, t_act act)
{
	intmax_t	res;
	intmax_t	tmp;

	res = eval(rule->rule.may_match.maybe_rule, str, matches, act);
	while (res >= 0)
	{
		tmp = eval(rule->rule.may_match.maybe_rule, str, matches, act);
		if (tmp < 0)
			break ;
		res += tmp;
	}
	return (res);
}

intmax_t	match_aster(t_peg_rule *rule, SV *str, char **matches, t_act act)
{
	intmax_t	res;
	intmax_t	tmp;

	res = eval(rule->rule.may_match.maybe_rule, str, matches, act);
	if (res < 0)
		res = 0;
	while (res)
	{
		tmp = eval(rule->rule.may_match.maybe_rule, str, matches, act);
		if (tmp < 0)
			break ;
		res += tmp;
	}
	return (res);
}

intmax_t	match_quest(t_peg_rule *rule, SV *str, char **matches, t_act act)
{
	intmax_t	res;

	res = 0;
	if (eval(rule->rule.may_match.maybe_rule, str, matches, PEEK) >= 0)
		res = eval(rule->rule.may_match.maybe_rule, str, matches, act);
	return (res);
}
