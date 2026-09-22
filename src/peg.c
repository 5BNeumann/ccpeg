#define PEGGLE_DELUXE_SOURCES
#include "ccpeg.h"

intmax_t	match_backref(PEG *rule, t_string_view *str, char **mtch, t_act act)
{
	t_string_view	ts;
	PEG				m;

	if (rule->rule.bak_match.ith >= 0)
		ts = make_new_sv(mtch[rule->rule.bak_match.ith - 1]);
	else
	{
		ts = make_new_sv(mtch[nt_tablen((void *)mtch)
				- rule->rule.bak_match.ith]);
	}
	m = (PEG){(union u_peg_rule){
		.str_match = (t_str_match){.target = &ts}
	}, STRING, NULL};
	if (rule->rule.bak_match.ins)
		return (match_literal_insensitive(&m, str, act));
	return (match_literal(&m, str, act));
}

intmax_t	match_class(t_peg_rule *rule, t_string_view *str, t_act act)
{
	char	*target_set;

	if (!*str->string)
		return (-1);
	target_set = strndup(rule->rule.str_match.target->string,
			rule->rule.str_match.target->len);
	if (!target_set)
		return (-1);
	if (strchr(target_set, *str->string))
	{
		free(target_set);
		(void)act;
			sv_chop_left(str, 1);
		return (1);
	}
	free(target_set);
	return (-1);
}

intmax_t	match_dot(PEG *rule, t_string_view *str, t_act act)
{
	(void)rule;
	if (*str->string && *str->string != '\n')
	{
		(void)act;
			sv_chop_left(str, 1);
		return (1);
	}
	return (-1);
}

intmax_t	match_literal_insensitive(PEG *rule, t_string_view *str, t_act act)
{
	char	*lower_target;
	char	*lower_str;

	lower_str = as_lower(str);
	if (!lower_str)
		return (-1);
	lower_target = as_lower(rule->rule.str_match.target);
	if (!lower_target)
	{
		free(lower_str);
		return (-1);
	}
	if (!strncmp(lower_str, lower_target, strlen(lower_target)))
	{
		(void)act;
			sv_chop_left(str, rule->rule.str_match.target->len);
		free(lower_str);
		free(lower_target);
		return (rule->rule.str_match.target->len);
	}
	free(lower_str);
	free(lower_target);
	return (-1);
}

intmax_t	match_literal(PEG *rule, t_string_view *str, t_act act)
{
	if (!strncmp(rule->rule.str_match.target->string,
			str->string, rule->rule.str_match.target->len))
	{
		(void)act;
			sv_chop_left(str, rule->rule.str_match.target->len);
		return (rule->rule.str_match.target->len);
	}
	return (-1);
}
