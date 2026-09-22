#ifndef CCPEG_INT_H
# define CCPEG_INT_H
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <sys/param.h>
# define PEG t_peg_rule
# define SV t_string_view
# define MAX_MATCHES 20

typedef struct s_peg_rule	t_peg_rule;

typedef enum e_lookup
{
	NOT,
	POS,
	NEG,
}	t_lookup;

typedef enum e_act
{
	PEEK,
	POKE
}	t_act;

enum e_maybe_type
{
	QUESTION,
	ASTERISK,
	PLUS
};

enum e_pos
{
	START,
	END,
};

typedef struct s_string_view
{
	char		*string;
	uintmax_t	len;
	char		*orig;
}	t_string_view;

typedef struct s_bak_match
{
	intmax_t	(*match)(PEG *, SV *, char **, t_act);
	int32_t		ith;
	bool		ins;
}	t_bak_match;

typedef struct s_cap_match
{
	intmax_t	(*match)(PEG *, SV *, char **, t_act);
	PEG			*rule;
}	t_cap_match;

typedef struct s_chc_match
{
	intmax_t	(*match)(PEG *, SV *, char **, t_act);
	PEG			*rule;
}	t_chc_match;

typedef struct s_lkp_match
{
	intmax_t	(*match)(PEG *, SV *, char **, t_act);
	PEG			*rule;
	t_lookup	ltype;
}	t_lkp_match;

typedef struct s_str_match
{
	intmax_t		(*match)(PEG *, SV *, t_act);
	SV	*target;
}	t_str_match;

typedef struct s_nch_match
{
	enum e_pos	pos;
}	t_nch_match;

typedef struct s_may_match
{
	intmax_t			(*match)(PEG *, SV *, char **, t_act);
	enum e_maybe_type	maybe_type;
	PEG					*maybe_rule;
}	t_may_match;

typedef struct s_dot_match
{
	intmax_t		(*match)(PEG *, SV *, t_act);
}	t_dot_match;

enum e_rule_type
{
	BACKREF,
	CAPTURE,
	CHOICHE,
	STRING,
	ANCHOR,
	LOOKUP,
	GROUP,
	MAYBE,
	DOT,
	SEQ,
};

typedef struct s_peg_rule
{
	union u_peg_rule
	{
		t_bak_match	bak_match;
		t_cap_match	cap_match;
		t_chc_match	chc_match;
		t_str_match	str_match;
		t_nch_match	nch_match;
		t_lkp_match	lkp_match;
		t_may_match	may_match;
		t_dot_match	dot_match;
	}					rule;
	enum e_rule_type	type;
	PEG					*next;
}	t_peg_rule;

/* *************** */
/*   STRING VIEW   */
/* *************** */

SV			make_new_sv(char *s);
void		sv_chop_left(SV *s, intmax_t i);
void		sv_chop_right(SV *s, intmax_t i);

/* *************** */
/*  GENERAL UTILS  */
/* *************** */

PEG			*mk_peg_rule(enum e_rule_type type);
void		swp_matches(char **m1, char **m2);
char		**copy_matches(char **matches);
char		*as_lower(SV *s);
PEG			*tail(PEG *list);

/* *************** */
/*     PARSING     */
/* *************** */

/* ******* */
/*  UTILS  */
/* ******* */

void		*free_nt_tab(char **str, const int32_t alloc_count);
uintmax_t	nt_tablen(void **tab);
char		*push_char(char *s, char c);
void		skip_spc(char **str);

/* ******* */
/*  MAIN   */
/* ******* */

PEG			*parse_choiche(char **s);
char		*parse_class(char **str);
char		*parse_lit(char **str);
PEG			*parse_par(char **s);

/* *************** */
/*    MATCHING     */
/* *************** */

intmax_t	destroy_capture(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_capture(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_choiche(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_backref(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_group(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_aster(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_quest(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_plus(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_lkp(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_seq(PEG *rule, SV *str, char **matches, t_act act);
intmax_t	match_literal_insensitive(PEG *rule, SV *str, t_act act);
intmax_t	match_literal(PEG *rule, SV *str, t_act act);
intmax_t	match_class(PEG *rule, SV *str, t_act act);
intmax_t	match_dot(PEG *rule, SV *str, t_act act);

intmax_t	eval(PEG *self, SV *str, char **matches, t_act a);

/* *************** */
/*  CONSTRUCTION   */
/* *************** */

PEG			*mk_backref(int32_t ith, bool insensitive);
PEG			*mk_x_or_moar(PEG *tw, char moar_type);
PEG			*mk_class_match(char *cclass);
PEG			*mk_lit_match(char *str, bool ins);
PEG			*mk_lkp(PEG	*rule, t_lookup l);
PEG			*mk_choiche(PEG *rule);
PEG			*mk_cap(PEG *rule);
PEG			*mk_grp(PEG *rule);
PEG			*mk_seq(PEG *rule);
PEG			*parse(char *str);
PEG			*mk_strt_anch(void);
PEG			*mk_dstr_cap(void);
PEG			*mk_nd_anch(void);
PEG			*mk_dot(void);

#endif
