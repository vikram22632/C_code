#ifndef __LKD_LIST_HEADER
#define __LKD_LIST_HEADER

#include "common.h"

typedef enum
{
	BUBBLE_SORT = 1,
	INSERT_SORT,
	MERGE_SORT,
	SELECT_SORT,
	QUICK_SORT
}
LL_SORT_TYPE;

typedef VBOOL (*lldata_compFunc)(any_t, any_t);

typedef struct _llist
{
	int		elemCnt;
	any_t	anchor;
}
LIST_STYPE, * LIST_PTYPE;

extern int listInit(LIST_PTYPE);

extern int list_length(LIST_PTYPE list);
extern VBOOL list_empty(LIST_PTYPE list);

extern int list_addAtBeg(LIST_PTYPE list, any_t data);
extern int list_addAtEnd(LIST_PTYPE list, any_t data);
extern int list_insertafter(LIST_PTYPE list, any_t data, any_t llnode);
extern int list_insertbefore(LIST_PTYPE list,any_t data, any_t llnode);
extern void list_unlink(LIST_PTYPE list, any_t llnode);
extern void list_unlinkall(LIST_PTYPE list);

extern any_t list_first(LIST_PTYPE list);
extern any_t list_last(LIST_PTYPE list);
extern any_t list_next(LIST_PTYPE list, any_t llnode);
extern any_t list_prev(LIST_PTYPE list, any_t llnode);

extern any_t list_find(LIST_PTYPE list, any_t data);

#endif
