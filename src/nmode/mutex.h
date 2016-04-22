#ifndef __NMODE_ENP_MUTEX_H__
#define __NMODE_ENP_MUTEX_H__

#include <pthread.h>

#define ENP_INIT   pthread_mutexattr_t pthread_mutexattr_default; \
                   pthread_mutexattr_init(&pthread_mutexattr_default); \
                   pthread_mutex_init(&_mutex, &pthread_mutexattr_default);

#define ENP_CLOSE  pthread_mutex_destroy(&_mutex);

#define ENP_LOCK   pthread_mutex_lock(&_mutex);
#define ENP_UNLOCK pthread_mutex_unlock(&_mutex);

#endif // __ENP_MUTEX_H__
