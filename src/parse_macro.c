#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

PEG	*parse_suff(char **s, t_lookup l)
{
	PEG	*res;

	res = parse_par(s);
	if (**s == '+' || **s == '*' || **s == '?')
		res = mk_x_or_moar(res, *(*s)++);
	return (mk_lkp(res, l));
}

PEG	*parse_pref(char **s)
{
	if (**s == '&')
	{
		++*s;
		return (parse_suff(s, POS));
	}
	if (**s == '!')
	{
		++*s;
		return (parse_suff(s, NEG));
	}
	return (parse_suff(s, NOT));
}

PEG	*parse_seq(char **s)
{
	PEG	*rules;
	PEG	*tmp;

	skip_spc(s);
	rules = NULL;
	while (true)
	{
		if (!**s || **s == '/' || **s == ')' || **s == '}')
			break ;
		tmp = parse_pref(s);
		if (!rules)
			rules = tmp;
		else
			tail(rules)->next = tmp;
		skip_spc(s);
	}
	return (mk_seq(rules));
}

PEG	*parse_choiche(char **s)
{
	PEG	*choiche;

	choiche = parse_seq(s);
	skip_spc(s);
	while (**s == '/')
	{
		++*s;
		skip_spc(s);
		tail(choiche)->next = parse_seq(s);
		skip_spc(s);
	}
	if (tail(choiche) != choiche)
		return (mk_choiche(choiche));
	return (choiche);
}

PEG	*parse(char *str)
{
	PEG	*res;

	skip_spc(&str);
	res = parse_choiche(&str);
	skip_spc(&str);
	if (*str)
	{
		errno = EINVAL;
		free_peg(res);
		return (NULL);
	}
	return (res);
}
