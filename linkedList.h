#ifndef __LKD_LIST_HEADER
#define __LKD_LIST_HEADER

#include "common.h"

typedef struct _llNode
{
    struct _llNode *    next;
    struct _llNode *    prev;
    any_t               data;
}LLNODE_STYPE, * LLNODE_PTYPE;

#endif
