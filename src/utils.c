#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

void	swp_matches(char **m1, char **m2)
{
	uintmax_t	i;

	i = 0;
	while (i < MAX_MATCHES)
	{
		free(m1[i]);
		if (*m2)
		{
			m1[i] = *m2;
			++m2;
		}
		else
			m1[i] = NULL;
		++i;
	}
}

char	**copy_matches(char **matches)
{
	char		**copy;
	uintmax_t	i;

	copy = ft_calloc(MAX_MATCHES + 1, sizeof(char *));
	i = 0;
	while (matches[i])
	{
		copy[i] = ft_strdup(matches[i]);
		++i;
	}
	return (copy);
}

char	*as_lower(t_string_view *s)
{
	uintmax_t	i;
	char		*res;

	res = ft_strndup(s->string, s->len);
	i = 0;
	while (res[i])
	{
		res[i] = ft_tolower(res[i]);
		i++;
	}
	return (res);
}

PEG	*tail(PEG *list)
{
	PEG	*current;

	current = list;
	while (current && current->next)
		current = current->next;
	return (current);
}

PEG	*mk_peg_rule(enum e_rule_type type)
{
	PEG	*res;

	res = ft_calloc(1, sizeof(PEG));
	res->type = type;
	if (type == STRING)
		res->rule.str_match.target = ft_calloc(1, sizeof(t_string_view));
	return (res);
}
