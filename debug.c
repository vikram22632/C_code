/*
 * ============================================================================
 * File Name: debug.c
 *
 * Description: This file contains the functions meant to be used in case the
 *              coder requires to output debug logs for their program
 *
 * Revision History: ver 1.0.0
 * ============================================================================
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"

#ifdef DEBUG
static FILE *   dbgFp   = NULL;

/*
 * ============================================================================
 * Function Name: initDebug
 *
 * Description	: This function is meant to initialize the debugging module for
 *                  and application. This function decides whether the debug
 *                  logs would go to stderr(default) or to some other file. The
 *                  logs from execution of previous instance of application will
 *                  get overwritten. It is supposed to be called only once in
 *                  the life of the program (beginning), do not call it again.
 *
 * Input Params	:   char * szFileName -> the name of the file for debug logs
 *
 * Output Params: 0 (SUCCESS) / (-1) FAILURE
 * ============================================================================
 */
int initDebug(char * szFileName)
{
    int     rv  = 0;
    
    if((szFileName != NULL) & (strlen(szFileName) != 0)) {
        dbgFp = fopen(szFileName, "w");
        if(dbgFp == NULL) {
            fprintf(stderr, "ERROR: Couldnt open file for debug log writing\n");
            rv = -1;
        }
    } else {
        dbgFp = stderr;
    }
    
    return rv;
}

/*
 * ============================================================================
 * Function Name: DBG_TRACE
 *
 * Description	: This function is supposed to output debug logs in the stderr
 *
 * Input Params	:   char * szfmt -> format for the data to be printed in logs
 *                  ... -> variable arguments
 *
 * Output Params: none
 * ============================================================================
 */
void DBG_TRACE(char * szFmt, ...)
{
    char	szLocFmt[256]	= "";
    va_list	arguments;
    
    va_start(arguments, szFmt);
    sprintf(szLocFmt, "\n%s", szFmt);
    vfprintf(dbgFp, szLocFmt, arguments);
    va_end(arguments);
}

/*
 * ============================================================================
 * Function Name: TDBG_TRACE
 *
 * Description	: This function is supposed to be a timed debug trace, i.e it
 *                  will provide the time information as well in the logs,
 *                  apart from the information supplied by the coder.
 *
 * Input Params	:   char * szfmt -> format for the data to be printed in logs
 *                  ... -> variable arguments
 *
 * Output Params: none
 * ============================================================================
 */
void TDBG_TRACE(char * szFmt, ...)
{
    char        szLocFmt[256]	= "";
    time_t      timer;
    va_list     arguments;
    struct tm * pstTime;
    
    time(&timer);
    pstTime = gmtime(&timer);
    
    va_start(arguments, szFmt);
    /* Format: dd/mm/yyyy-hhmmss: data */
    sprintf(szLocFmt, "\n%02d/02d/%04d-%02%02%02: %s", pstTime->tm_mday,
                pstTime->tm_mon, pstTime->tm_year + 1900, pstTime->tm_hour,
                pstTime->tm_min, pstTime->tm_sec, szFmt);
    vfprintf(dbgFp, szLocFmt, arguments);
    va_end(arguments);
}

#endif

/*
 * ============================================================================
 * End of file debug.c
 * ============================================================================
 */
