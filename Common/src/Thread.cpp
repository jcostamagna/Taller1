/*
 * server_thread.cpp
 *
 *  Created on: 28/04/2015
 *      Author: juan
 */
#include <cstddef>
#include "Thread.h"


void* Thread::starter(void* data){
	Thread* realThread =(Thread*) data;
	realThread->run();
	return NULL;
}

void Thread::start(){
	pthread_create(&(this->thread),NULL,starter,this);
	}

void Thread::join(){
	pthread_join((this->thread), NULL);
	}






