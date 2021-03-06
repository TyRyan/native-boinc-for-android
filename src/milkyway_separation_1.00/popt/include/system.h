/**
 * \file popt/system.h
 */

#include "popt_config.h"

#if defined(_MSC_VER) || defined(__MINGW32__)
# define _CRT_SECURE_NO_WARNINGS 1
#endif


#if defined (__GLIBC__) && defined(__LCLINT__)
/*@-declundef@*/
/*@unchecked@*/
extern __const __int32_t *__ctype_tolower;
/*@unchecked@*/
extern __const __int32_t *__ctype_toupper;
/*@=declundef@*/
#endif

#include <ctype.h>


#ifdef __GNUC__
# undef alloca
# define alloca __builtin_alloca
#else
# ifdef HAVE_ALLOCA_H
#  include <alloca.h>
# else
#  ifndef _AIX
/* AIX alloca decl has to be the first thing in the file, bletch! */
char *alloca ();
#  endif
# endif
#endif


/* XXX isspace(3) has i18n encoding signednesss issues on Solaris. */
#define	_isspaceptr(_chp)	isspace((int)(*(unsigned char *)(_chp)))

#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#ifdef HAVE_MCHECK_H
#include <mcheck.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(HAVE_UNISTD_H) && !defined(__LCLINT__)
#include <unistd.h>
#endif


#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(x)
#endif
#define UNUSED(x) x __attribute__((__unused__))


#ifdef _MSC_VER
#  define inline __inline
#endif


#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <malloc.h>
#include <process.h>
#define F_OK 0
#define R_OK 4
#define W_OK 2
#define X_OK 1

#define S_IRWXG 00000070
#define S_IRWXO 00000007
#define S_ISUID 00040000
#define S_ISGID 00020000
#define S_ISVTX 00010000

/* I haven't discovered a better way to work around these format
   specifier problems */
#define LONG_LONG_FORMAT "I64d"


/* CHECKME */
#define S_IWGRP 00000020
#define S_IWOTH 00000002

#define S_ISREG(m) ((m)&_S_IFREG)


/* Documentation claims these are in limits.h, but it seems to be a lie */
/* Microsoft documentation http://msdn.microsoft.com/en-us/library/k15zsh48.aspx */

#if !defined(FLT_MIN)
#define FLT_MIN 1.175494351e-38F
#endif

#if !defined(FLT_MAX)
#define FLT_MAX 3.402823466e+38F
#endif

typedef int uid_t;

#ifdef _WIN64
typedef __int64 ssize_t;
#else
typedef int ssize_t;
#endif /* _WIN64 */

#define srandom srand
#define random rand
#define access _access
#define strdup _strdup
#define execvp _execvp
#define strtoll _strtoi64
#define read _read
#define open _open
#define close _close
#define lseek _lseek
#define execvp _execvp

/* Pretend to be root to replace these */
static inline int setuid(UNUSED(int x)) { return 1; }

static inline int getuid(void) { return 0; }

static inline int seteuid(UNUSED(int x)) { return 1; }
static inline int geteuid(void) { return 0; }

static inline int setgid(UNUSED(int x)) { return 1; }
static inline int getgid(void) { return 0; }

static inline int setegid(UNUSED(int x)) { return 1; }


#else

#define LONG_LONG_FORMAT "lld"

#endif /* defined(_MSC_VER) || defined(__MINGW32__) */

#ifdef __NeXT
/* access macros are not declared in non posix mode in unistd.h -
 don't try to use posix on NeXTstep 3.3 ! */
#include <libc.h>
#endif


/*@-incondefs@*/
/*@mayexit@*/ /*@only@*/ /*@out@*/ /*@unused@*/
void * xmalloc (size_t size)
	/*@globals errno @*/
	/*@ensures maxSet(result) == (size - 1) @*/
	/*@modifies errno @*/;

/*@mayexit@*/ /*@only@*/ /*@unused@*/
void * xcalloc (size_t nmemb, size_t size)
	/*@ensures maxSet(result) == (nmemb - 1) @*/
	/*@*/;

/*@mayexit@*/ /*@only@*/ /*@unused@*/
void * xrealloc (/*@null@*/ /*@only@*/ void * ptr, size_t size)
	/*@ensures maxSet(result) == (size - 1) @*/
	/*@modifies *ptr @*/;

/*@mayexit@*/ /*@only@*/ /*@unused@*/
char * xstrdup (const char *str)
	/*@*/;
/*@=incondefs@*/

#if !defined(HAVE_STPCPY)
/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
static inline char * stpcpy (char *dest, const char * src) {
    register char *d = dest;
    register const char *s = src;

    do
	*d++ = *s;
    while (*s++ != '\0');
    return d - 1;
}
#endif

/* Memory allocation via macro defs to get meaningful locations from mtrace() */
#if defined(HAVE_MCHECK_H) && defined(__GNUC__)
#define	vmefail()	(fprintf(stderr, "virtual memory exhausted.\n"), exit(EXIT_FAILURE), NULL)
#define	xmalloc(_size) 		(malloc(_size) ? : vmefail())
#define	xcalloc(_nmemb, _size)	(calloc((_nmemb), (_size)) ? : vmefail())
#define	xrealloc(_ptr, _size)	(realloc((_ptr), (_size)) ? : vmefail())
#define xstrdup(_str)   (strcpy((malloc(strlen(_str)+1) ? : vmefail()), (_str)))
#else
#define	xmalloc(_size) 		malloc(_size)
#define	xcalloc(_nmemb, _size)	calloc((_nmemb), (_size))
#define	xrealloc(_ptr, _size)	realloc((_ptr), (_size))
#define	xstrdup(_str)	strdup(_str)
#endif  /* defined(HAVE_MCHECK_H) && defined(__GNUC__) */

#if defined(HAVE___SECURE_GETENV) && !defined(__LCLINT__)
#define	getenv(_s)	__secure_getenv(_s)
#endif

#if 0
/* Include configmake.h autogenerated from Makefile.am */
#include "configmake.h"
#endif

#include "popt.h"

