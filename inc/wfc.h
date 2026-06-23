#ifndef WFC_H
# define WFC_H

typedef enum e_nodeType	e_nodeType;
enum e_nodeType {
	E_LINE,
	E_JUNCTION,
	E_END
};


typedef struct s_node	t_node;
struct s_node {
	e_nodeType	nType;
};

typedef struct s_form	t_form;
struct s_form {
	uint64_t	forms;
};

#define	WFC_ZONE_SIZE	64 
struct wfcZone {
	t_form	*case[WFC_ZONE_SIZE][WFC_ZONE_SIZE];
};


#endif
