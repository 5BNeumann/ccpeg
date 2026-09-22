#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

intmax_t	match_lkp(PEG *self, SV *str, char **matches, t_act act)
{
	intmax_t	result;
	char		**mcpy;
	SV			saved;

	mcpy = copy_matches(matches);
	saved = *str;
	if (self->rule.lkp_match.ltype == NOT)
	{
		free_nt_tab((void *)mcpy, MAX_MATCHES);
		return (eval(self->rule.lkp_match.rule, str, matches, act));
	}
	else if (self->rule.lkp_match.ltype == POS)
		result = -(eval(self->rule.lkp_match.rule, str, matches, act) < 0);
	else
		result = -(eval(self->rule.lkp_match.rule, str, matches, act) >= 0);
	*str = saved;
	swp_matches(matches, mcpy);
	free(mcpy);
	return (result);
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
	char		**mcpy;
	SV			saved;

	mcpy = copy_matches(matches);
	saved = *str;
	res = eval(rule->rule.may_match.maybe_rule, str, matches, act);
	if (res < 0)
	{
		res = 0;
		*str = saved;
		swp_matches(matches, mcpy);
		free(mcpy);
	}
	else
		free_nt_tab((void *)mcpy, MAX_MATCHES);
	return (res);
}
