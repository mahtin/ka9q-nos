#ifndef	_SOCKET_H
#define	_SOCKET_H

#ifndef	_GLOBAL_H
#include "global.h"
#endif

#include <stdarg.h>

#ifndef	_MBUF_H
#include "mbuf.h"
#endif

#ifndef _PROC_H
#include "proc.h"
#endif

#ifndef _SOCKADDR_H
#include "sockaddr.h"
#endif

/* Local IP wildcard address */
#define	INADDR_ANY	0x0L

/* IP protocol numbers */
/* now in internet.h */

/* TCP port numbers */
#define	IPPORT_ECHO	7	/* Echo data port */
#define	IPPORT_DISCARD	9	/* Discard data port */
#define	IPPORT_FTPD	20	/* FTP Data port */
#define	IPPORT_FTP	21	/* FTP Control port */
#define IPPORT_TELNET	23	/* Telnet port */
#define IPPORT_SMTP	25	/* Mail port */
#define	IPPORT_MTP	57	/* Secondary telnet protocol */
#define	IPPORT_FINGER	79	/* Finger port */
#define	IPPORT_TTYLINK	87	/* Chat port */
#define IPPORT_POP	109	/* pop2 port */
#define	IPPORT_NNTP	119	/* Netnews port */
#define	IPPORT_LOGIN	513	/* BSD rlogin port */
#define	IPPORT_TERM	5000	/* Serial interface server port */

/* UDP port numbers */
#define	IPPORT_DOMAIN	53
#define	IPPORT_BOOTPS	67
#define	IPPORT_BOOTPC	68
#define	IPPORT_PHOTURIS	468	/* Photuris Key management */
#define	IPPORT_RIP	520
#define	IPPORT_REMOTE	1234	/* Pulled out of the air */
#define	IPPORT_BSR	5000	/* BSR X10 interface server port (UDP) */

#define	AF_INET		0
#define	AF_AX25		1
#define AF_NETROM	2
#define	AF_LOCAL	3
#define	NAF		4

#define	SOCK_STREAM	0
#define	SOCK_DGRAM	1
#define	SOCK_RAW	2
#define SOCK_SEQPACKET	3

#undef	EWOULDBLOCK
#define	EWOULDBLOCK	100
#define	ENOTCONN	101
#define	ESOCKTNOSUPPORT	102
#define	EAFNOSUPPORT	103
#define	EISCONN		104
#define	EOPNOTSUPP	105
#define	EALARM		106
#define	EABORT		107
#undef	EINTR
#define	EINTR		108
#define	ECONNREFUSED	109
#define EMSGSIZE	110
#define	EADDRINUSE	111
#define	EMIN		100
#define	EMAX		112

extern char *Sock_errlist[];

/* In socket.c: */
extern int Axi_sock;	/* Socket listening to AX25 (there can be only one) */

extern int accept(int s,struct sockaddr *peername,int *peernamelen);
extern int bind(int s,struct sockaddr *name,int namelen);
extern int close_s(int s);
extern int connect(int s,struct sockaddr *peername,int peernamelen);
extern char *eolseq(int s);
extern void freesock(struct proc *pp);
extern int getpeername(int s,struct sockaddr *peername,int *peernamelen);
extern int getsockname(int s,struct sockaddr *name,int *namelen);
extern int listen(int s,int backlog);
extern int recv_mbuf(int s,struct mbuf **bpp,int flags,struct sockaddr *from,int *fromlen);
extern int send_mbuf(int s,struct mbuf **bp,int flags,struct sockaddr *to,int tolen);
extern int settos(int s,int tos);
extern int shutdown(int s,int how);
extern int socket(int af,int type,int protocol);
extern void sockinit(void);
extern int sockkick(int s);
extern int socklen(int s,int rtx);
extern struct proc *sockowner(int s,struct proc *newowner);
extern int usesock(int s);
extern int socketpair(int af,int type,int protocol,int sv[]);

/* In sockuser.c: */
extern void flushsocks(void);
extern int recv(int s,void *buf,int len,int flags);
extern int recvfrom(int s,void *buf,int len,int flags,struct sockaddr *from,int *fromlen);
extern int send(int s,void *buf,int len,int flags);
extern int sendto(int s,void *buf,int len,int flags,struct sockaddr *to,int tolen);

/* In file sockutil.c: */
extern char *psocket(void *p);
extern char *sockerr(int s);
extern char *sockstate(int s);

/* In file tcpsock.c: */
extern int start_tcp(uint16 port,char *name,void (*task)(),int stack);
extern int stop_tcp(uint16 port);

#endif	/* _SOCKET_H */
