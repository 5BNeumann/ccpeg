#define PEGGLE_DELUXE_SOURCES
#include "peggle_deluxe.h"

// @doc nt_tablen
// @kind func
// @desc Returns the length of the null terminated tab tab.
// @param tab: void **, Null terminated tab to get the length of.
// @returns uintmax_t, length of tab.
uintmax_t	nt_tablen(void **tab)
{
	uintmax_t	len;

	len = 0;
	while (tab && tab[len])
		len++;
	return (len);
}

void	*free_nt_tab(char **str, const int32_t alloc_count)
{
	int32_t	i;

	i = 0;
	while (str && str[i] && i < alloc_count)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}


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

	copy = calloc(MAX_MATCHES + 1, sizeof(char *));
	i = 0;
	while (matches[i])
	{
		copy[i] = strdup(matches[i]);
		++i;
	}
	return (copy);
}

char	*as_lower(t_string_view *s)
{
	uintmax_t	i;
	char		*res;

	res = strndup(s->string, s->len);
	i = 0;
	while (res[i])
	{
		res[i] = tolower(res[i]);
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

	res = calloc(1, sizeof(PEG));
	res->type = type;
	if (type == STRING)
		res->rule.str_match.target = calloc(1, sizeof(t_string_view));
	return (res);
}
