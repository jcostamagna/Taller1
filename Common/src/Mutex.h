/*
 * server_Mutex.h
 *
 *  Created on: 26 May 2015
 *      Author: osboxes
 */

#ifndef COMMON_SRC_MUTEX_H_
#define COMMON_SRC_MUTEX_H_

#include <pthread.h>

class Mutex {
private:
	pthread_mutex_t mutex;
	pthread_cond_t _cond;
	Mutex(const Mutex& object);
	Mutex& operator=(const Mutex& object);
public:
	Mutex();
	void lock();
	void unlock();
	void signal();
	void wait();
	~Mutex();
};

#endif /* COMMON_SRC_MUTEX_H_ */
