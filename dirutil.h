#ifndef	_DIRUTIL_H
#define	_DIRUTIL_H

#ifndef	_GLOBAL_H
#include "global.h"
#endif

/* In dirutil.c */
extern FILE *dir(char *path,int full);
extern int filedir(char *name,int times,char *ret_str);
extern int getdir(char *path,int full,FILE *file);

/* In pathname.c: */
extern char *pathname(char *cd,char *path);

#endif /* _DIRUTIL_H */

