#ifndef __DBG_HEADER
#define __DBG_HEADER

#ifdef DEBUG
extern int initDebug(char *);
extern void DBG_TRACE(char *, ...);
extern void TDBG_TRACE(char *, ...);
#else
#define initDebug(0);
#define DBG_TRACE(...);
#define TDBG_TRACE(...);
#endif

#endif
