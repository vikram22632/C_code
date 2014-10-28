#ifndef __DBG_HEADER
#define __DBG_HEADER

#ifdef DEBUG
extern void DBG_TRACE(char *, ...);
#else
#define DBG_TRACE(...);
#endif

#endif
