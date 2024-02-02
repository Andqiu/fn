#ifndef __OS_TYPE_H__
#define __OS_TYPE_H__

#ifndef WIN32
#define BOOL bool
#define UINT  unsigned int
#define LPCSTR const char *
#ifndef TRUE
#define TRUE  true;
#endif
#ifndef FALSE
#define FALSE false;
#endif
typedef unsigned int DWORD;
typedef long LONG;
typedef const char LPCTSTR;
typedef unsigned int UINT32;
#endif

// lock for anysystem...
#if defined(__WINDOWS_DS__) || defined(__WINDOWS_ASIO__) || defined(WIN32)
#include <WinSock2.h>
#include <windows.h>

//#include <process.h>

typedef unsigned long ThreadHandle;
typedef CRITICAL_SECTION StreamMutex;

#elif defined(__LINUX_ALSA__) || defined(__UNIX_JACK__) || defined(__LINUX_OSS__) || defined(__MACOSX_CORE__) || defined (ANDROID)
// Using pthread library for various flavors of unix.
#include <pthread.h>

typedef pthread_t ThreadHandle;
typedef pthread_mutex_t StreamMutex;

#endif


#if defined(__WINDOWS_DS__) || defined(__WINDOWS_ASIO__) || defined(WIN32)
#define MUTEX_INITIALIZE(A) InitializeCriticalSection(A)
#define MUTEX_DESTROY(A)    DeleteCriticalSection(A)
#define MUTEX_LOCK(A)       EnterCriticalSection(A)
#define MUTEX_UNLOCK(A)     LeaveCriticalSection(A)
#elif defined(__LINUX_ALSA__) || defined(__UNIX_JACK__) || defined(__LINUX_OSS__) || defined(__MACOSX_CORE__) || defined(ANDROID)
// pthread API
//for ios
#ifndef PTHREAD_MUTEX_RECURSIVE_NP
#    define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#  endif

#define MUTEX_INITIALIZE(A)  {    \
	pthread_mutexattr_t attr;     \
	pthread_mutexattr_init(&attr);\
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP); \
	pthread_mutex_init(A, &attr);       \
	pthread_mutexattr_destroy(&attr);}
                                 
#define MUTEX_DESTROY(A)    pthread_mutex_destroy(A)
#define MUTEX_LOCK(A)       pthread_mutex_lock(A)
#define MUTEX_UNLOCK(A)     pthread_mutex_unlock(A)
#else
#define MUTEX_INITIALIZE(A) abs(*A) // dummy definitions
#define MUTEX_DESTROY(A)    abs(*A) // dummy definitions
#endif



//°²È«É¾³ýÖ¸Õë
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(NULL != p) { delete (p);     (p)=NULL; } }
#endif


#ifndef WIN32
#define LF_FACESIZE         32

typedef struct tagLOGFONTA
{
	LONG      lfHeight;
	LONG      lfWidth;
	LONG      lfEscapement;
	LONG      lfOrientation;
	LONG      lfWeight;
	unsigned char      lfItalic;
	unsigned char      lfUnderline;
	unsigned char      lfStrikeOut;
	unsigned char      lfCharSet;
	unsigned char      lfOutPrecision;
	unsigned char      lfClipPrecision;
	unsigned char      lfQuality;
	unsigned char      lfPitchAndFamily;
	char      lfFaceName[LF_FACESIZE];
} LOGFONT;


#include <sys/time.h> 
#include <mach/clock.h>
#include <mach/mach.h>

typedef mach_port_t		clock_serv_t;

inline double timeGetTime() 
{ 
	double uptime = 0.0;
    struct timeval t;
       
    gettimeofday(&t, NULL);
       
    uptime = (double)t.tv_sec+ (double)t.tv_usec/1000000.0;
       
    return uptime;
} 


#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#endif

#endif //__OS_TYPE_H__

