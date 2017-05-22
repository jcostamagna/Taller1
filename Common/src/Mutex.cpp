/*
 * server_Mutex.cpp
 *
 *  Created on: 26 May 2015
 *      Author: osboxes
 */

#include "Mutex.h"

#include <iostream>

Mutex::Mutex() {
	::pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&_cond, NULL);
}

void Mutex::lock(){
	pthread_mutex_lock(&mutex);
}

void Mutex::unlock(){
	pthread_mutex_unlock(&mutex);
}

void Mutex::signal(){
	pthread_cond_broadcast(&_cond);
}

void Mutex::wait(){
	pthread_cond_wait(&_cond, &mutex);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&_cond);
}

