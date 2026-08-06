#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <stddef.h>
# include <ctype.h>
# include <stdbool.h>

typedef enum e_optType		e_optType;
typedef enum e_genType		e_genType;
typedef enum e_printType	e_printType;
typedef enum e_colorType	e_colorType;

typedef struct s_parsArg	t_parsArg;

typedef struct s_nonConstArt	t_nonConstArt;
typedef struct s_art			t_art;
typedef struct s_tab			t_tab;

typedef struct s_clrSet		t_clrSet;

typedef struct s_oneClrRules	t_oneClrRules;
typedef struct s_clrRules	t_clrRules;

typedef struct s_iClr		t_iClr;
typedef struct s_clr		t_clr;

typedef struct s_startList	t_startList;
typedef struct s_start		t_start;

typedef struct s_cluster	t_cluster;
typedef struct s_point	t_point;
typedef struct s_petri	t_petri;

typedef uint64_t	(*t_getClusterWeightFn)(const t_cluster *cluster);
typedef uint64_t	(*t_getPointWeightFn)(const t_point *point, const t_cluster *cluster);
typedef uint8_t		(*t_chosePossibilityFn)(const uint8_t possibility);
typedef uint8_t		(*t_getPossibilityMaskFn)(const t_point *point, const t_cluster *cluster);

#endif
