#ifndef CCPEG_H
# define CCPEG_H
# include <stdbool.h>
# ifdef PEGGLE_DELUXE_SOURCES
#  include "peggle_deluxe_int.h"
# endif
# ifndef PEG
#  define PEG t_peg_rule
# endif
# ifndef MAX_MATCHES
#  define MAX_MATCHES 20
# endif

typedef struct s_peg_rule	t_peg_rule;

void			*free_peg(PEG *p);
bool			match(PEG *peg, char *str, char **matches);
PEG				*peg(char *pat);

#endif // CCPEG_H
