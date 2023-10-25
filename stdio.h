#ifndef	_STDIO_H
#define	_STDIO_H

#ifndef	_GLOBAL_H
#include "global.h"
#endif

#define	EOL_LEN	3

#define	_fd_type(fd)	(((fd) >> 13) & 3)
#define	_fd_seq(fd)	((fd) & 8191)
#define	_mk_fd(fd,type)	((fd) | ((type) << 13))

struct _file{
	unsigned cookie;		/* Detect bogus file pointers */
#define	_COOKIE	0xdead
	int refcnt;
	struct _file *prev;
	struct _file *next;

	int fd;			/* File, socket or asy descriptor */
	long offset;		/* Seek offset, type == _FL_FILE only */

	enum {
		_FL_FILE,	/* Associated with file */
		_FL_SOCK,	/* Associated with network socket */
		_FL_ASY,	/* Asynch port */
		_FL_DISPLAY,	/* Associated with display driver */
		_FL_PIPE	/* Pipe mode */
	} type;

	enum {
		_IOFBF=1,	/* Full buffering */
		_IOLBF,		/* Line buffering */
		_IONBF		/* No buffering */
	} bufmode;		/* Output buffering mode */

	struct {
		unsigned int err:1;	/* Error on stream */
		unsigned int eof:1;	/* EOF seen */
		unsigned int ascii:1;	/* Ascii (newline translate) mode */
		unsigned int append:1;	/* Always seek to end before writing */
		unsigned int tmp:1;	/* Delete on close */
		unsigned int partread:1;/* Allow partial reads from fread() */
	} flags;
	struct mbuf *obuf;	/* Output buffer */
	struct mbuf *ibuf;	/* Input buffer */
	char eol[EOL_LEN];	/* Text mode end-of-line sequence, if any */
	int bufsize;		/* Size of buffer to use */
	void *ptr;		/* File name or display pointer */
};

typedef struct _file FILE;

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#undef	NULL
#define	NULL	0
#define	BUFSIZ	2048
#define	EOF	(-1)
#define	L_tmpnam	13

#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#ifndef _PROC_H
#include "proc.h"
#endif

#define	stdout	Curproc->output
#define	stdin	Curproc->input
#define	stderr	Curproc->output

#define	STREAM_BINARY	0
#define	STREAM_ASCII	1

#define	FULL_READ	0
#define	PART_READ	1

extern FILE *asyopen(char *name,char *mode);
extern int close(int fd);
extern FILE *displayopen(char *mode,int noscrol,int sfsize);
extern int fblock(FILE *fp,int mode);
extern int fclose(FILE *fp);
extern void fcloseall(void);
extern FILE *fdopen(int handle,char *mode);
extern FILE *fdup(FILE *fp);
extern int fflush(FILE *fp);
extern int fgetc(FILE *fp);
extern int _fgetc(FILE *fp);
extern char *fgets(char *buf,int len,FILE *fp);
extern void flushall(void);
extern int fmode (FILE *fp,int mode);
extern char *fpname(FILE *fp);
extern int fprintf(FILE *fp,char *fmt,...);
extern int fputc(int c,FILE *fp);
extern int fputs(char *buf,FILE *fp);
extern size_t fread(void *ptr,size_t size,size_t n,FILE *fp);
extern FILE *freopen(char *name,char *mode,FILE *fp);
extern int fseek(FILE *fp,long offset,int whence);
extern long ftell(FILE *fp);
extern size_t fwrite(void *ptr,size_t size,size_t n,FILE *fp);
extern char *gets(char *s);
extern void perror(const char *s);
extern FILE *pipeopen(void);
extern int printf(char *fmt,...);
extern int puts(char *s);
extern int rename(const char *,const char *);
extern void setbuf(FILE *fp,char *buf);
extern int seteol(FILE *fp,char *seq);
extern int setvbuf(FILE *fp,char *buf,int type,int size);
extern int sprintf(char *,char *, ...);
extern int sscanf(char *,char *,...);	/* From regular library */
extern FILE *tmpfile(void);
extern char *tmpnam(char *);	/* From regular library */
extern int ungetc(int c,FILE *fp);
extern int unlink(const char *);	/* From regular library */
extern int vfprintf(FILE *fp,char *fmt, void *args);
extern int vprintf(char *fmt, void *args);
extern int vsprintf(char *,char *,void *);

extern int _clrtmp;	/* Flag controlling wipe of temporary files on close */

/* Macros */
#define	feof(fp)	((fp)->flags.eof)
#define ferror(fp)	((fp)->flags.err)
#define	fileno(fp)	((fp) != NULL ? (fp)->fd : -1)
#define fopen(s,m)	(freopen((s),(m),NULL))
#define	putc(c,fp)	(fputc((c),(fp)))
#define	getc(fp)	(fgetc((fp)))
#define	getchar()	(getc(stdin))
#define	clearerr(fp)	((fp)->flags.eof = (fp)->flags.err = 0)
#define rewind(fp)	((void)fseek((fp),0L,SEEK_SET),clearerr((fp)))
#define	putchar(c)	(putc((c),stdout))

#endif /* _STDIO_H */
