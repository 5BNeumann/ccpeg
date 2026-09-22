#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

void	*free_peg(PEG *p)
{
	if (!p)
		return (NULL);
	if (p->next)
		p->next = free_peg(p->next);
	if (p->type == MAYBE)
		p->rule.may_match.maybe_rule = free_peg(p->rule.may_match.maybe_rule);
	else if (p->type == LOOKUP)
		p->rule.lkp_match.rule = free_peg(p->rule.lkp_match.rule);
	else if (p->type == STRING)
	{
		free(p->rule.str_match.target->orig);
		p->rule.str_match.target->orig = NULL;
		free(p->rule.str_match.target);
		p->rule.str_match.target = NULL;
	}
	else if (p->type == CHOICHE || p->type == SEQ)
		p->rule.chc_match.rule = free_peg(p->rule.chc_match.rule);
	else if (p->type == CAPTURE || p->type == GROUP)
		p->rule.cap_match.rule = free_peg(p->rule.cap_match.rule);
	free(p);
	return (NULL);
}

bool	match(PEG *peg, char *str, char **matches)
{
	t_string_view	strsv;

	strsv = make_new_sv(str);
	if (peg->type == ANCHOR)
	{
		if (peg->rule.nch_match.pos == END)
			return (false);
		return (eval(peg->next, &strsv, matches, POKE) >= 0);
	}
	return (eval(peg, &strsv, matches, POKE) >= 0);
}

PEG	*peg(char *pat)
{
	return (parse(pat));
}
