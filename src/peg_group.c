#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

intmax_t	match_seq(PEG *rule, SV *str, char **mtch, t_act act)
{
	PEG				*current;
	intmax_t		res[2];
	char			**mcpy;
	SV				saved;

	mcpy = copy_matches(mtch);
	saved = *str;
	current = rule->rule.chc_match.rule;
	res[0] = 0;
	while (current)
	{
		res[1] = eval(current, str, mtch, act);
		if (res[1] < 0)
		{
			*str = saved;
			swp_matches(mtch, mcpy);
			free(mcpy);
			return (-1);
		}
		res[0] += res[1];
		current = current->next;
	}
	free_nt_tab((void *)mcpy, MAX_MATCHES);
	return (res[0]);
}

intmax_t	match_choiche(PEG *rule, SV *str, char **mtch, t_act act)
{
	PEG				*current;
	intmax_t		tmp;
	char			**mcpy;
	SV				saved;

	mcpy = copy_matches(mtch);
	saved = *str;
	current = rule->rule.chc_match.rule;
	while (current)
	{
		tmp = eval(current, str, mtch, act);
		if (tmp >= 0)
		{
			free_nt_tab((void *)mcpy, MAX_MATCHES);
			return (tmp);
		}
		current = current->next;
	}
	*str = saved;
	swp_matches(mtch, mcpy);
	free(mcpy);
	return (-1);
}

intmax_t	match_group(PEG *rule, SV *str, char **mtch, t_act act)
{
	return (eval(rule->rule.cap_match.rule, str, mtch, act));
}

intmax_t	match_capture(PEG *rule, SV *str, char **mtch, t_act act)
{
	intmax_t	r;

	r = eval(rule->rule.cap_match.rule, str, mtch, act);
	if (r >= 0 && act == POKE)
		mtch[nt_tablen((void *)mtch)] = strndup(str->string - r, r);
	return (r);
}

intmax_t	destroy_capture(PEG *rule, SV *str, char **mtch, t_act act)
{
	intmax_t	matchn;

	(void)rule;
	(void)str;
	matchn = nt_tablen((void *)mtch);
	if (matchn > 0 && act == POKE)
	{
		free(mtch[matchn - 1]);
		mtch[matchn - 1] = NULL;
	}
	return (0);
}
