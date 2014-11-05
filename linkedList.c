/*
 * ============================================================================
 * File Name: linkedList.c
 *
 * Description:
 *
 * Revision History:
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

/* defining a node of the linked list */
typedef struct _llNode
{
	struct _llNode * next;
	struct _llNode * prev;
	any_t data;
}LLNODE_STYPE, * LLNODE_PTYPE;

/*
 * ============================================================================
 * Function Name: listInit
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
int listInit(LIST_PTYPE list)
{
	int				rv		= SUCCESS;
	LLNODE_PTYPE	anchor	= NULL;

	anchor = (LLNODE_PTYPE) malloc(sizeof(LLNODE_STYPE));
	if(anchor == NULL) {
		fprintf(stderr, "%s: FAILED to allocate memory\n", __FUNCTION__);
		rv = FAILURE;
	}
	else {
		memset(list, 0x00, sizeof(LIST_STYPE));
		memset(anchor, 0x00, sizeof(LLNODE_STYPE));

		list->anchor = anchor;
	}

	return rv;
}

/*
 * ============================================================================
 * Function Name: list_length
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
int list_length(LIST_PTYPE list)
{
	return list->elemCnt;
}

/*
 * ============================================================================
 * Function Name: list_empty
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
VBOOL list_empty(LIST_PTYPE list)
{
	VBOOL	rv	= V_FALSE;

	if(list->elemCnt == 0) {
		rv = V_TRUE;
	}

	return rv;
}

/*
 * ============================================================================
 * Function Name: list_addAtBeg
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
int list_addAtBeg(LIST_PTYPE list, any_t data)
{
	int				rv	= SUCCESS;
	LLNODE_PTYPE	tmp	= NULL;
	LLNODE_PTYPE	a	= NULL;
	LLNODE_PTYPE	f	= NULL;

	/* Allocate memory for the new element to be added to the list */
	tmp = (LLNODE_PTYPE) malloc(sizeof(LLNODE_STYPE)); 
	if(tmp == NULL) {
		fprintf(stderr, "\n%s: FAILED to allocate memory", __FUNCTION__);
		rv = FAILURE;
	}
	else {
		memset(tmp, 0x00, sizeof(LLNODE_STYPE));
		tmp->data = data;
		a = (LLNODE_PTYPE)(list->anchor);
		tmp->prev = a;

		/* Get the first element of the list */
		f = (LLNODE_PTYPE) list_first(list);
		if(f == NULL)
		{
			/* Prepending the first element to the list */
			a->prev = tmp;
			tmp->next = a;
		}
		else
		{
			/* Prepending nth element to the list */
			tmp->next = f;
			f->prev = tmp;
		}

		/* Updating the anchor and the element count */
		a->next = tmp;
		list->elemCnt += 1;
	}

	return rv;
}

/*
 * ============================================================================
 * Function Name: list_addAtEnd
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
int list_addAtEnd(LIST_PTYPE list, any_t data)
{
	int				rv	= SUCCESS;
	LLNODE_PTYPE	tmp	= NULL;
	LLNODE_PTYPE	a	= NULL;
	LLNODE_PTYPE	l	= NULL;

	/* Allocate memory for the new element to be added to the list */
	tmp = (LLNODE_PTYPE) malloc(sizeof(LLNODE_STYPE)); 
	if(tmp == NULL) {
		fprintf(stderr, "\n%s: FAILED to allocate memory", __FUNCTION__);
		rv = FAILURE;
	}
	else {
		memset(tmp, 0x00, sizeof(LLNODE_STYPE));
		tmp->data = data;
		a = (LLNODE_PTYPE)(list->anchor);
		tmp->next = a;

		/* Get the current last element in the list */
		l = (LLNODE_PTYPE) list_last(list);
		if(l == NULL)
		{
			/* Appending the first element to the list */
			a->next = tmp;
			tmp->prev = a;
		}
		else
		{
			/* Adding nth element to the list */
			tmp->prev = l;
			l->next = tmp;
		}

		/* Updating the anchor and the element count */
		a->prev = tmp;
		list->elemCnt += 1;
	}

	return rv;
}

/*
 * ============================================================================
 * Function Name: list_insertafter
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
int list_insertafter(LIST_PTYPE list, any_t data, any_t llnode)
{
	int				rv	= 0;
	LLNODE_PTYPE	tmp	= NULL;

	if(llnode == NULL) {
		/* Simply add the element to the end of the list. */
		rv = list_addAtEnd(list, data);
	}
	else {
		LLNODE_PTYPE	cur	= (LLNODE_PTYPE) llnode;

		/* Assuming that llnode exists in the list, trusting the coding
		 * abilities of the coder for this */
		tmp = (LLNODE_PTYPE) malloc(sizeof(LLNODE_STYPE));
		if(tmp == NULL) {
			fprintf(stderr, "%s: FAILED to allocate memory\n", __FUNCTION__);
			rv = FAILURE;
		}
		else {
			memset(tmp, 0x00, sizeof(LLNODE_STYPE));
			tmp->data = data;

			/* Update the list with the new node */
			tmp->next = cur->next;
			tmp->prev = cur;
			cur->next = tmp;
			tmp->next->prev = tmp;

			/* Update the elements count in the list */
			list->elemCnt += 1;
		}
	}

	return rv;
}

/*
 * ============================================================================
 * Function Name: list_insertbefore
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
int list_insertbefore(LIST_PTYPE list,any_t data, any_t llnode)
{
	int				rv	= 0;
	LLNODE_PTYPE	tmp	= NULL;

	if(llnode == NULL) {
		/* Simply add the element to the end of the list. */
		rv = list_addAtBeg(list, data);
	}
	else {
		LLNODE_PTYPE	cur	= (LLNODE_PTYPE) llnode;

		/* Assuming that llnode exists in the list, trusting the coding
		 * abilities of the coder for this */
		tmp = (LLNODE_PTYPE) malloc(sizeof(LLNODE_STYPE));
		if(tmp == NULL) {
			fprintf(stderr, "%s: FAILED to allocate memory\n", __FUNCTION__);
			rv = FAILURE;
		}
		else {
			memset(tmp, 0x00, sizeof(LLNODE_STYPE));
			tmp->data = data;

			/* Update the list with the new node */
			tmp->next = cur;
			tmp->prev = cur->prev;
			cur->prev = tmp;
			tmp->prev->next = tmp;

			/* Update the elements count in the list */
			list->elemCnt += 1;
		}
	}

	return rv;
}

/*
 * ============================================================================
 * Function Name: list_unlink
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
void list_unlink(LIST_PTYPE list, any_t llnode)
{
	LLNODE_PTYPE	cur	= (LLNODE_PTYPE) llnode;
	LLNODE_PTYPE	a	= (LLNODE_PTYPE) (list->anchor);

	if((cur->next == a) && (cur->prev == a)) {
		/* Unlinking the only element present in the list */
		a->next = NULL;
		a->prev = NULL;
	}
	else {
		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
	}

	free(cur);
	list->elemCnt -= 1;

	return;
}

/*
 * ============================================================================
 * Function Name: list_unlinkall
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
void list_unlinkall(LIST_PTYPE list)
{
	LLNODE_PTYPE	cur	= NULL;
	LLNODE_PTYPE	tmp	= NULL;
	LLNODE_PTYPE	a	= (LLNODE_PTYPE) (list->anchor);

	cur = (LLNODE_PTYPE) list_first(list);
	if(cur != NULL)
	{
		while(cur != a)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
	}

	a->next = NULL;
	a->prev = NULL;
	list->elemCnt = 0;

	return;
}

/*
 * ============================================================================
 * Function Name: list_first
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
any_t list_first(LIST_PTYPE list)
{
	return ((LLNODE_PTYPE)(list->anchor))->next;
}

/*
 * ============================================================================
 * Function Name: list_last
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
any_t list_last(LIST_PTYPE list)
{
	return ((LLNODE_PTYPE)(list->anchor))->prev;
}

/*
 * ============================================================================
 * Function Name: list_next
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
any_t list_next(LIST_PTYPE list, any_t llnode)
{
	LLNODE_PTYPE	nxt	= NULL;
	LLNODE_PTYPE	cur	= (LLNODE_PTYPE) llnode;
	LLNODE_PTYPE	a	= (LLNODE_PTYPE)(list->anchor);

	if(cur->next != a) {
		nxt = cur->next;
	}

	return nxt;
}

/*
 * ============================================================================
 * Function Name: list_prev
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
any_t list_prev(LIST_PTYPE list, any_t llnode)
{
	LLNODE_PTYPE	prev	= NULL;
	LLNODE_PTYPE	cur	= (LLNODE_PTYPE) llnode;
	LLNODE_PTYPE	a	= (LLNODE_PTYPE)(list->anchor);

	if(cur->prev != a) {
		prev = cur->prev;
	}

	return prev;
}

/*
 * ============================================================================
 * Function Name: list_find
 *
 * Description	: 
 *
 * Input Params	:
 *
 * Output Params: none
 * ============================================================================
 */
any_t list_find(LIST_PTYPE list, any_t data)
{
	LLNODE_PTYPE	cur	= NULL;
	LLNODE_PTYPE	a	= (LLNODE_PTYPE)(list->anchor);

	cur = (LLNODE_PTYPE) list_first(list);
	if(cur != NULL) {
		while(cur != a)
		{
			if(cur->data == data) {
				break;
			}

			cur = cur->next;
		}
	}

	return cur;
}

/*
 * ============================================================================
 * End of file linkedList.c
 * ============================================================================
 */

