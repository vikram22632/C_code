/*
 * ============================================================================
 * File Name: debug.c
 *
 * Description:
 *
 * Revision History:
 * ============================================================================
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"

#ifdef DEBUG
/*
 * ============================================================================
 * Function Name: DBG_TRACE
 *
 * Description	:
 *
 * Input Params	:
 *
 * Output Params:
 * ============================================================================
 */
void DBG_TRACE(char * szFmt, ...)
{
		char	szLocFmt[256]	= "";
		va_list	arguments;

		va_start(arguments, szFmt);

		sprintf(szLocFmt, "\n%s", szFmt);
		vfprintf(stderr, szLocFmt, arguments);

		va_end(arguments);
}
#endif

/*
 * ============================================================================
 * End of file debug.c
 * ============================================================================
 */
