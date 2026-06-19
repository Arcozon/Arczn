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

struct wfc
{
	
};


#endif
